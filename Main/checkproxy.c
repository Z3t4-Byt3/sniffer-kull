#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <netinet/in.h>
#include <curl/curl.h>
#include "../Headers/kcolor.h"
#include "../Headers/kurl.h"

int main (int argc, char *argv[]) {

  setlocale (LC_ALL, "");

  if (argc != 2)
    print_error (" Uso: checkproxy <ip>");

  CURL *curl;
  CURLcode res;

  curl = curl_easy_init ();
  if (curl) {

    struct string str;
    init_string (&str);

    char ip_url[50 + INET_ADDRSTRLEN + 1];
    snprintf (ip_url, strlen (argv[1]) + 50, 
        "http://www.shroomery.org/ythan/proxycheck.php?ip=%s", argv[1]);

    curl_easy_setopt (curl, CURLOPT_URL, ip_url);
    curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt (curl, CURLOPT_WRITEDATA, &str);

    res = curl_easy_perform (curl);
    if (res != CURLE_OK)
      print_error ("[-] Error em curl_easy_perform()");

    if (strcmp (str.data, "Y") == 0)
      printf ("IP: %s é um proxy\n", argv[1]);
    else
      printf ("IP: %s não é um proxy\n", argv[1]);

    free (str.data);
    curl_easy_cleanup (curl);

  }

  return 0;

}
