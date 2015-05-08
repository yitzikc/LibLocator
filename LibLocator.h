/*
 * LibLocator.h
 *
 *  Created on: May 7, 2015
 *      Author: yitzikc
 */

#ifndef UTILS_LIBLOCATOR_H_
#define UTILS_LIBLOCATOR_H_

#include <string>
#include <map>

class LibLocator {
public:
	LibLocator();
	~LibLocator();
	void ClearCache();

	// Return the path of the first instance of the specified library and version, or an empty string if not found
	// The library name should be given without the leading 'lib' and the '.so' extension.
	std::string GetLibPath(const std::string& name, const std::string& ver = "") const;

	std::string GetLibDir(const std::string& name, const std::string& ver = "") const;
	std::string GetPathRelativeToLibDir(const std::string& relativePath, const std::string& name, const std::string& ver = "") const;

private:
	mutable std::map<std::string, std::string> m_PathCache;
};

#endif /* UTILS_LIBLOCATOR_H_ */

