//
//  main.c
//  Yahoo! Stock Quotes (StockQuotes)
//
//  Created by LaVelton R. Carroway on 05/27/2014.
//  Copyright (c) 2014 Rochee Software, LLC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <curl/curl.h>

// Dividends from stocks, REITs, equity mutual funds, or other equity securities
// Interest from owning bonds, certificates of deposit, other other cash and cash equivalents

int main(int argc, const char * argv[])
{
    CURL *curl = curl_easy_init();
    time_t currtime;
    time(&currtime);
    struct tm *now = localtime(&currtime);
    char MyStockName[1024];
    const char *MyStockTicker[] = {"AAPL", "CTL", "ESV", "FTR", "HCN", "HCP", "POM", "RIG", "T", "TE", "WIN"};

    fprintf(stdout,"Yahoo! Finance Stock Quotes v1.0\n");
    fprintf(stdout,"Date: %i/%i/%d\n\n", now->tm_mon,now->tm_mday,now->tm_year);

    // Indicator Display Colors
    //
    //	red="\E[31;40m"
    //	green="\E[32;40m"
    //	white="\E[37;40m"
    //	yellow="\E[33;40m"
    //	bold="\033[1m"
    //	normal="\033[0m"

    fprintf(stdout,"Equity Indices\n");
    fprintf(stdout,"Name        Price \n");
    fprintf(stdout,"\u2594\u2594\u2594\u2594\u2594       \u2594\u2594\u2594\u2594\u2594\u2594\n");

    for(int i = 0; i < sizeof(MyStockTicker)/sizeof(MyStockTicker[0]); i++)
    {
        strcpy(MyStockName, "http://download.finance.yahoo.com/d/quotes.csv?s=");
        strcat(MyStockName, MyStockTicker[i]);
        strcat(MyStockName, "&f=l1");
        if(curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, MyStockName);
            fprintf(stdout,"%-12s", MyStockTicker[i]);
            curl_easy_perform(curl);
        }
    }

    if(curl)
    {
        curl_easy_cleanup(curl);
    }

    fprintf(stdout,"\n");

    return 0;
}
