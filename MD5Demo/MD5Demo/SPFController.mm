//
//  SPFController.m
//  MD5Demo
//
//  Created by pengfei sun on 5/29/13.
//  Copyright (c) 2013 pengfei sun. All rights reserved.
//

#import "SPFController.h"
#include "CCMD5.h"
@implementation SPFController
-(IBAction)OkButton:(id)sender
{
    NSLog(@"fuck");
    self.m_text_label.stringValue = self.m_text_edit.stringValue;
    
    CCMD5 md5;
//    std::string ssss = [self.m_text_label.stringValue UTF8String];
//    std::string sss = md5.getMD5String((uchar*)(ssss.c_str()), ssss.length());
//    uchar* uuuu = new uchar[185];
//    for (int i = 0; i < 185; i ++) {
//        uuuu[i] = 'c';
//    }
//     std::string sss = md5.getMD5String(uuuu, 185);
//    self.m_text_label.stringValue = [NSString stringWithFormat:@"%s", sss.c_str()];
    for (int j = 0;j < 1000 ; j ++) {
        uchar* uuuu = new uchar[j+1];
        for (int i = 0; i < j; i ++) {
            uuuu[i] = 'c';
        }
        std::string sss = md5.getMD5String(uuuu, j);
        delete [] uuuu;
//        self.m_text_label.stringValue = [NSString stringWithFormat:@"%s", sss.c_str()];
    }
    NSLog(@"sssss");
}
@end
