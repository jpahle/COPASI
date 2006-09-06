/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CDirEntry.h,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/06 17:38:52 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CDirEntry
#define COPASI_CDirEntry

#include <string>
#include <vector>

/**
 * This class provides an OS independent interface to directory entries
 * such as files and directories.
 */
class CDirEntry
  {
  public:
    /**
     * The character used to separate directory entries.
     */
    static const std::string Separator;

    /**
     * Check whether the directory entry specified by 'path' is
     * a file.
     * @param const std::string & path
     * @return bool isFile
     */
    static bool isFile(const std::string & path);

    /**
     * Check whether the directory entry specified by 'path' is
     * is a directory.
     * @param const std::string & path
     * @return bool isDir
     */
    static bool isDir(const std::string & path);

    /**
     * Check whether the directory entry specified by 'path' exists.
     * @param const std::string & path
     * @return bool exist
     */
    static bool exist(const std::string & path);

    /**
     * Check whether the directory entry specified by 'path' is
     * is readable.
     * @param const std::string & path
     * @return bool isReadable
     */
    static bool isReadable(const std::string & path);

    /**
     * Check whether the directory entry specified by 'path' is
     * writable.
     * @param const std::string & path
     * @return bool isWritable
     */
    static bool isWritable(const std::string & path);

    /**
     * Returns the base name, i.e., the directory path and the
     * the suffix are removed from 'path'.
     * @param const std::string & path
     * @return std::string baseName
     */
    static std::string baseName(const std::string & path);

    /**
     * Returns the file name, i.e., the directory path is removed from 'path'.
     * @param const std::string & path
     * @return std::string fileName
     */
    static std::string fileName(const std::string & path);

    /**
     * Returns the directory path to the parent directoryu, i.e.,
     * the file name or directory name are removed from 'path'.
     * @param const std::string & path
     * @return std::string dirName
     */
    static std::string dirName(const std::string & path);

    /**
     * Returns the suffix, i.e., the directory path and the
     * the base name are removed from 'path'.
     * @param const std::string & path
     * @return std::string basename
     */
    static std::string suffix(const std::string & path);

    /**
     * Create the directory 'dir' in the parent directory 'parent'.
     * @param const std::string & dir
     * @param const std::string & parent (Default: current working directory)
     * @return bool success
     */
    static bool createDir(const std::string & dir,
                          const std::string & parent = "");

    /**
     * Create a name for a temporary directory entry. The directory entry
     * will be located in the directory given
     * @param const std::string & dir
     * @param const std::string & suffix
     * @return std::string tmpName
     */
    static std::string createTmpName(const std::string & dir,
                                     const std::string & suffix);

    /**
     * Move a file from. If to is the directory the filename of from is
     * appended.
     * @param const std::string & from
     * @param const std::string & to
     * @return bool success
     */
    static bool move(const std::string & from,
                     const std::string & to);

    /**
     * Removes a file or directory specified by path.
     * @param const std::string & path
     * @return bool success
     */
    static bool remove(const std::string & path);

    /**
     * Remove files or directories matching the pattern in directory dir.
     * @param const std::string & pattern
     * @param const std::string & dir
     * @return bool success
     */
    static bool removeFiles(const std::string & pattern,
                            const std::string & dir);

    /**
     * Compiles the pattern to a patternList. Valid wildcards in the pattern are:
     * '*' matches any number of characters and '?' matches exactly one character.
     * @param const std::string & pattern
     * @return std::vector< std::string > patternList
     */
    static std::vector< std::string > compilePattern(const std::string & pattern);

    /**
     * Compare the name against the pattern list and returns whether the
     * name matches. The patternList can be created from a pattern by the
     * compilePattern method.
     * @param const std::string & name
     * @param const std::vector< std::string > & patternList
     * @return bool match
     */
    static bool match(const std::string & name,
                      const std::vector< std::string > & patternList);

    /**
     * Checks whether the given path is relative
     * @return bool isRelative
     */
    static bool isRelativePath(const std::string & path);

    /**
     * Makes the absolute path relative to the path given in relativeTo
     * @param std::string & absolutePath
     * @param const std::string & relativeTo
     * @return bool success
     */
    static bool makePathRelative(std::string & absolutePath,
                                 const std::string & relativeTo);

    /**
     * Makes the relative path absolute to the path given in absoluteTo
     * @param std::string & relativePath
     * @param const std::string & absoluteTo
     * @return bool success
     */
    static bool makePathAbsolute(std::string & relativePath,
                                 const std::string & absoluteTo);

  private:
    /**
     * This private methods checks whether the active section matches the
     * secified patter. The section is automatically advanced to allow
     * repeated calls. On the first call 'at' must be 0. The parameters
     * 'at' and 'after' must not be changed outside this method.
     * @param const std::string & name
     * @param const std::string pattern
     * @param std::string::size_type & at
     * @param std::string::size_type & after
     * @return bool match
     */
    static bool matchInternal(const std::string & name,
                              const std::string pattern,
                              std::string::size_type & at,
                              std::string::size_type & after);
  };

#endif // COPASI_CDirEntry
