//
//  MYFileManager.cpp
//  testAnimation
//
//  Created by pengfei sun on 5/23/13.
//
//

#ifdef TARGET_OS_MAC
    #include <Cocoa/Cocoa.h>
#elif TARGET_OS_IPHONE
    #include <UIKit/UIKit.h>
#endif
#include <fstream>
#include "FileManager.h"
using namespace std;

const char* CCFileManager::getDocumentPath()
{
    NSString* str = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString*ful = [NSString stringWithFormat:@"%@%@",str,@"/"];
    return [ful UTF8String];
}
const char* CCFileManager::getTempPath()
{
    NSString* str = NSTemporaryDirectory();
    return [str UTF8String];
}
const char* CCFileManager::getFullPathInDocument(const char* filename)
{
    NSString* str = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString*ful = [NSString stringWithFormat:@"%@%@%s",str,@"/",filename];
    return [ful UTF8String];
}
const char* CCFileManager::getFullPathInTmp(const char* filename)
{
    NSString* str = NSTemporaryDirectory();
    NSString*ful = [NSString stringWithFormat:@"%@%s",str,filename];
    return [ful UTF8String];
}

long CCFileManager::getFileLength(const char* filepath)
{
    std::string path(filepath);

    long length = 0;
    fstream file;
    file.open(filepath,ios::in);
    
    if (file.good()) {
        file.seekg(0,ios::end);
        length = file.tellg();
    }    
    return length;
}
bool CCFileManager::getFileData(const char* filepath, char *filedata, long filelength )
{
    std::string path(filepath);
    bool res = true;
    fstream file;
    file.open(filepath,ios::in);
    
    if (file.good()) {
        file.read(filedata, filelength);
    }
    else
    {
        res = false;
    }
    return res;
}
const char* CCFileManager::getFullPath(const char* filename)
{
    NSString* str = [NSString stringWithFormat:@"%s",filename ];
    NSRange range = [str rangeOfString:@"." options:NSBackwardsSearch];
    NSRange rangtype = NSMakeRange(0, range.location +1);
    NSRange rangname = NSMakeRange(range.location, str.length - range.location);
    NSString* type = [str stringByReplacingCharactersInRange:rangtype withString:@""];
    NSString* name = [str stringByReplacingCharactersInRange:rangname withString:@""];
    NSString*strfulpath = [[NSBundle mainBundle]pathForResource:name ofType:type];
    return [strfulpath UTF8String];
}
bool CCFileManager::writeDataToFile(const char* filepath,const char *filedata, long filelength )
{
    bool res = true;
    fstream file;
    file.open(filepath,ios::out);
    
    if (file.good()) {
        file.write(filedata, filelength);
    }
    else
    {
        res = false;
    }
    file.close();
    return res;
}