//
//  NSURLRequest+OAuth.m
//  YelpAPISample
//
//  Created by Thibaud Robelain on 7/2/14.
//  Copyright (c) 2014 Yelp Inc. All rights reserved.
//

#import "NSURLRequest+OAuth.h"
#import "OAMutableURLRequest.h"
#include "ApiKey.h"

/**
 OAuth credential placeholders that must be filled by each user in regards to
 http://www.yelp.com/developers/getting_started/api_access
 */

@implementation NSURLRequest (OAuth)

+ (NSURLRequest *)requestWithHost:(NSString *)host
                             path:(NSString *)path
                           params:(NSDictionary *)params
                      consumerKey:(NSString*)consumerKey
                   consumerSecret:(NSString*)consumerSecret
                         tokenKey:(NSString*)tokenKey
                      tokenSecret:(NSString*)tokenSecret;

{
    NSURL *URL = [self _URLWithHost:host path:path queryParameters:params];
    
    if ([consumerKey length] == 0 || [consumerSecret length] == 0 || [tokenKey length] == 0 || [tokenSecret length] == 0) {
        NSLog(@"WARNING: Please enter your api v2 credentials before attempting any API request. You can do so in NSURLRequest+OAuth.m");
    }
    
    OAConsumer *consumer = [[OAConsumer alloc] initWithKey:consumerKey secret:consumerSecret];
    OAToken *token = [[OAToken alloc] initWithKey:tokenKey secret:tokenSecret];
    
    //The signature provider is HMAC-SHA1 by default and the nonce and timestamp are generated in the method
    OAMutableURLRequest *request = [[OAMutableURLRequest alloc] initWithURL:URL consumer:consumer token:token realm:nil signatureProvider:nil];
    [request setHTTPMethod:@"GET"];
    [request prepare]; // Attaches our consumer and token credentials to the request
    
    return request;
}

#pragma mark - URL Builder Helper

/**
 Builds an NSURL given a host, path and a number of queryParameters
 
 @param host The domain host of the API
 @param path The path of the API after the domain
 @param params The query parameters
 @return An NSURL built with the specified parameters
 */
+ (NSURL *)_URLWithHost:(NSString *)host path:(NSString *)path queryParameters:(NSDictionary *)queryParameters {
    
    NSMutableArray *queryParts = [[NSMutableArray alloc] init];
    for (NSString *key in [queryParameters allKeys]) {
        NSString *percentEncodedParamValue = [queryParameters[key] encodedURLParameterString];
        NSString *queryPart = [NSString stringWithFormat:@"%@=%@", key, percentEncodedParamValue];
        [queryParts addObject:queryPart];
    }
    
    NSURLComponents *components = [[NSURLComponents alloc] init];
    components.scheme = @"http";
    components.host = host;
    components.path = path;
    components.percentEncodedQuery = [queryParts componentsJoinedByString:@"&"];
    
    return [components URL];
}

@end
