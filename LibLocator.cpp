/*
 * LibLocator.cpp
 *
 *  Created on: May 7, 2015
 *      Author: yitzikc
 */

#include <assert.h>
#include <link.h>
#include <cstring>
#include <sstream>
#include <utility>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;
using namespace boost::filesystem;

#include "LibLocator.h"

LibLocator::LibLocator()  = default;

LibLocator::~LibLocator() = default;

void LibLocator::ClearCache()
{
	m_PathCache.clear();
}

namespace {


struct CbArg {
	string LibName;	// input
	string LibPath;	// output
};

int callback(struct dl_phdr_info *info, size_t size, void *data)
{
	CbArg* cbArg = reinterpret_cast<CbArg*>(data);
	if (strstr(info->dlpi_name, cbArg->LibName.c_str())) {
		cbArg->LibPath = info->dlpi_name;
		return 1;
	}
	return 0;
}


}	// anonymous namespace

string LibLocator::GetLibPath(const string& name, const string& ver) const
{
	ostringstream s;
	s << "lib" << name << ".so";
	if (!ver.empty()) {
		s << "." << ver;
	}
	string searchName = s.str();
	auto cacheIt = m_PathCache.find(searchName);
	if (cacheIt != m_PathCache.cend()) {
		return cacheIt->second;
	}

	CbArg arg { searchName };
	if (0 != dl_iterate_phdr(callback, &arg)) {
		string result = canonical(path(arg.LibPath)).string();
		m_PathCache[searchName] = result;
		return move(result);
	}

	return string();
}

string LibLocator::GetLibDir(const string& name, const string& ver) const
{
	string filePath = GetLibPath(name, ver);
	if (filePath.empty()) {
		return filePath;
	}

	return canonical(path(filePath).parent_path()).string();
}

string LibLocator::GetPathRelativeToLibDir(const string& relativePath, const string& name, const string& ver) const
{
	string dirPath = GetLibDir(name, ver);
	if (dirPath.empty()) {
		return dirPath;
	}

	return canonical(path(dirPath + "/" + relativePath)).string();
}

