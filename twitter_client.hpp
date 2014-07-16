#ifndef __TWITTERCLIENT_H__
#define __TWITTERCLIENT_H__
//
// Twitter クライアントの実装
//
// The MIT License (MIT)
//
// Copyright (c) <2014> chromabox <chromarockjp@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "oauth.hpp"
#include "http/httpcurl.hpp"
#include "picojson.h"


// Twitter REST1.1API用定義
namespace TwitterRest1_1
{
	// OAUTH 1
	static const std::string	OAUTH1_REQUEST_TOKEN	= "https://api.twitter.com/oauth/request_token";	// TemporaryCredentials
	static const std::string	OAUTH1_AUTHORIZE		= "https://api.twitter.com/oauth/authorize";		// ResourceOwnerAuth
	static const std::string	OAUTH1_ACCESS_TOKEN		= "https://api.twitter.com/oauth/access_token";		// TokenCredentials
	// Resource
	static const std::string	TL_RESOURCE_STATUSES_MEMTION	= "https://api.twitter.com/1.1/statuses/mentions_timeline.json";
	static const std::string	TL_RESOURCE_STATUSES_USERTL		= "https://api.twitter.com/1.1/statuses/user_timeline.json";
	static const std::string	TL_RESOURCE_STATUSES_HOMETL		= "https://api.twitter.com/1.1/statuses/home_timeline.json";
	static const std::string	TL_RESOURCE_STATUSES_RTOFME		= "https://api.twitter.com/1.1/statuses/retweets_of_me.json";
	// Tweets
	// Resource
	static const std::string	TW_RESOURCE_STATUSES_RTS_ID		= "https://api.twitter.com/1.1/statuses/retweets/%s.json";
	static const std::string	TW_RESOURCE_STATUSES_SHOW_ID	= "https://api.twitter.com/1.1/statuses/show.json";
	static const std::string	TW_RESOURCE_STATUSES_DEL_ID		= "https://api.twitter.com/1.1/statuses/destroy/%s.json";
	static const std::string	TW_RESOURCE_STATUSES_UPDATE		= "https://api.twitter.com/1.1/statuses/update.json";
	static const std::string	TW_RESOURCE_STATUSES_RETWEET	= "https://api.twitter.com/1.1/statuses/retweet/%s.json";
	
	// Search
	static const std::string	TW_SEARCH_TWEETS				= "https://api.twitter.com/1.1/search/tweets.json";
	
	
	// Help
	static const std::string	TW_HELP_CONFIGURATION			= "https://api.twitter.com/1.1/help/configuration.json";
	static const std::string	TW_HELP_RATE_LIMIT				= "https://api.twitter.com/1.1/application/rate_limit_status.json";
	
	
	// Other
	static const std::string	OAUTH_ANSWER_SCREENNAME			= "screen_name";
	static const std::string	OAUTH_ANSWER_USERID				= "user_id";
	// Search type
	static const std::string	SEARCH_RESTYPE_MIXED			= "mixed";
	static const std::string	SEARCH_RESTYPE_RECENT			= "recent";
	static const std::string	SEARCH_RESTYPE_POPULAR			= "popular";
	
	
}; // namespace TwitterRest1_1



class TwitterClient
{
	
protected:
	HTTPCurl	m_peer;
	OAuth		m_auth;
	bool		m_verbose;
	
	std::string	m_user_name;
	std::string	m_user_id;
	
	
	bool getRequest(const std::string url,HTTPRequestData &hdata,picojson::value &jsonval);
	bool postRequest(const std::string url,HTTPRequestData &hdata,picojson::value &jsonval);
	
public:
	TwitterClient();
	virtual ~TwitterClient();

	void setComsumerPair(const std::string &key,const std::string &sec);
	void setUserAccessPair(const std::string &key,const std::string &sec);
	
	void getUserAccessPair(std::string &key,std::string &sec);


	bool Authentication_GetURL(std::string &rurl);
	bool Authentication_Finish(const std::string &pin);
	
	bool getHomeTimeline(uint16_t count,
						const std::string &since_id,const std::string &max_id,
						bool include_rts,bool include_replies,
						picojson::array &rtimeline);
	
	bool postStatus(const std::string status);
	
	
	bool searchTweets(const std::string &q,const std::string &lang,const std::string &restype,
		const std::string & since_id,const std::string & max_id,picojson::array &rtimeline);
	
	inline void copyAuth(TwitterClient &rhs){
		m_auth			= rhs.m_auth;
	};

	inline std::string getMyUserName()					{return  m_user_name;}
	inline std::string getMyUserID()					{return  m_user_id;}
	
	inline void serVerbose(bool set)					{m_verbose = set;}
	bool		isVerbose()								{return m_verbose;}
	
	inline void vprint(const std::string &str){
		if(! isVerbose()) return;
		std::cout << str << std::endl;
	}
};


	
#endif // __TWITTERCLIENT_H__
