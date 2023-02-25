HTTP/1.1 200 OK
Server: nginx/1.21.5
Date: Fri, 24 Feb 2023 14:19:53 GMT
Content-Type: text/html; charset=utf-8
Content-Length: 7419
Last-Modified: Wed, 08 Feb 2023 16:14:20 GMT
Connection: keep-alive
Keep-Alive: timeout=15
ETag: "63e3ca5c-1cfb"
Accept-Ranges: bytes

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html><head><meta http-equiv="Content-Type" content="text/html; charset=utf-8"><link rel="alternate" type="application/rss+xml" title="nginx news" href="http://nginx.org/index.rss"><title>nginx news</title><style type="text/css">body { background: white; color: black; font-family: sans-serif; line-height: 1.4em; text-align: center; margin: 0; padding: 0; } #banner { background: black; color: #F2F2F2; line-height: 1.2em; padding: .3em 0; box-shadow: 0 5px 10px black; } #banner a { color: #00B140; } #main { text-align: left; margin: 0 auto; min-width: 32em; max-width: 64em; } #menu { float: right; width: 11em; padding: 0 .5em 1em .5em; border-left: 2px solid #DDD; } #content { margin-right: 13.5em; padding: 0 .2em 0 1.5em; } h1 { display: block; font-size: 3em; text-align: left; height: .7em; margin: 0; margin-bottom: .5em; } h1 img { width: 100%; } h2 { text-align: center; } p { text-align: justify; } table.news p { margin-top: 0; } table.news td { vertical-align: baseline; } table.news .date { text-align: right; padding-right: 0.5em; white-space: nowrap; } table.donors td { vertical-align: baseline; } table.donors li { text-align: left; } div.directive { background: #F2F2F2; line-height: 1em; margin: 1em 0 1em -1em; padding: .7em .7em .7em 1em; border-top: 2px solid #DDD; } div.directive th { padding-left: 0; padding-right: .5em; vertical-align: baseline; text-align: left; font-weight: normal; } div.directive td { vertical-align: baseline; } div.directive pre { padding: 0; margin: 0; } div.directive p { margin: .5em 0 0 .1em; font-size: .8em; } a.notrans { color: gray; text-decoration:none; } span.initial { font-size: 200%; float: left; padding-right: 10pt;} ul, ol { margin: .5em 0 1em 1em; padding: 0 .5em; } ol { list-style-position: inside; } li { text-align: justify; padding: .5em 0 0 1px; } .compact li { padding-top: 0; } dl { margin: .5em 0 1em 0; } dt { margin: .5em 0; } .compact dt { margin-bottom: .2em; } dd { margin-left: 1.5em; padding-left: 1px; text-align: justify; } td.list { background: #F2F2F2; } blockquote { margin: 1em 0 1em 1em; padding: .5em; } li blockquote, dd blockquote { margin: .7em 0; } blockquote.note { border: 1px dotted #999; line-height: 1.2em; text-align: justify; } blockquote.example { line-height: 1em; border-left: 1px solid #BBB; } blockquote.example pre { padding: 0; margin: 0; } sup { font-size: 50%; } .video { position: relative; padding-bottom: 56.25%; overflow: hidden; } .video iframe, .video object, .video embed { position: absolute; top:0; left:0; width:100%; height:100%; }</style><script>
        window.addEventListener("load", function(e) {
            fetch("banner/banner.html")
                .then((response) => response.text())
                .then((resp) => {
                    document.getElementById("banner").innerHTML = resp;
                })
                .catch((error) => {
                    console.warn(error);
                });
        });
    </script></head><body><div id="banner"></div><div id="main"><div id="menu"><h1><a href="/"><img src="/nginx.png" alt="nginx"></a></h1><div>english<br><a href="ru/">русский</a><br><br>news<br><a href="2022.html">2022</a><br><a href="2021.html">2021</a><br><a href="2020.html">2020</a><br><a href="2019.html">2019</a><br><a href="2018.html">2018</a><br><a href="2017.html">2017</a><br><a href="2016.html">2016</a><br><a href="2015.html">2015</a><br><a href="2014.html">2014</a><br><a href="2013.html">2013</a><br><a href="2012.html">2012</a><br><a href="2011.html">2011</a><br><a href="2010.html">2010</a><br><a href="2009.html">2009</a><br><br><a href="en/">about</a><br><a href="en/download.html">download</a><br><a href="en/security_advisories.html">security</a><br><a href="en/docs/">documentation</a><br><a href="en/docs/faq.html">faq</a><br><a href="en/books.html">books</a><br><a href="en/support.html">support</a><br><br><a href="http://trac.nginx.org/nginx">trac</a><br><a href="http://twitter.com/nginxorg">twitter</a><br><a href="https://www.nginx.com/blog/">blog</a><br><br><a href="https://unit.nginx.org/">unit</a><br><a href="en/docs/njs/">njs</a><br></div></div><div id="content"><h2>nginx news</h2>
            <table class="news">
        <tr><td class="date"><a name="2023-02-08"></a>2023-02-08</td><td><p><a href="https://quic.nginx.org/packages.html">nginx-quic packages</a>
are now available to preview HTTP3/QUIC implementation.
Check out the announcement
<a href="https://www.nginx.com/blog/binary-packages-for-preview-nginx-quic-http3-implementation/">blog post</a>
and
<a href="https://quic.nginx.org/">quic.nginx.org</a>
for installation instructions, documentation, and more.
</p></td></tr><tr><td class="date"><a name="2023-02-07"></a>2023-02-07</td><td><p><a href="en/docs/njs/index.html">njs-0.7.10</a>
version has been
<a href="en/docs/njs/changes.html#njs0.7.10">released</a>,
featuring extended
<a href="en/docs/njs/reference.html#builtin_crypto">WebCrypto API</a>,
extended
<a href="en/docs/njs/reference.html#ngx_fetch">Fetch API</a>
and
<a href="en/docs/njs/reference.html#xml">xml</a> module.
</p></td></tr><tr><td class="date"><a name="2022-12-15"></a>2022-12-15</td><td><p><a href="https://unit.nginx.org/">unit-1.29.0</a>
version has been
<a href="https://unit.nginx.org/news/2022/unit-1.29.0-released/">released</a>,
featuring initial
<a href="en/docs/njs/index.html">njs</a> support and per-app cgroups.
</p></td></tr><tr><td class="date"><a name="2022-12-13"></a>2022-12-13</td><td><p><a href="en/download.html">nginx-1.23.3</a>
mainline version has been released.
</p></td></tr><tr><td class="date"><a name="2022-11-17"></a>2022-11-17</td><td><p><a href="en/docs/njs/index.html">njs-0.7.9</a>
version has been
<a href="en/docs/njs/changes.html#njs0.7.9">released</a>.
</p></td></tr><tr><td class="date"><a name="2022-10-25"></a>2022-10-25</td><td><p><a href="en/docs/njs/index.html">njs-0.7.8</a>
version has been
<a href="en/docs/njs/changes.html#njs0.7.8">released</a>,
featuring the
<a href="en/docs/http/ngx_http_js_module.html#js_preload_object">js_preload_object</a>
directive.
</p></td></tr><tr><td class="date"><a name="2022-10-19"></a>2022-10-19</td><td><p><a href="en/download.html">nginx-1.22.1</a>
stable and
<a href="en/download.html">nginx-1.23.2</a>
mainline versions have been released,
with a fix for the
<a href="en/security_advisories.html">memory corruption and
memory disclosure</a>
vulnerabilities in the ngx_http_mp4_module (CVE-2022-41741, CVE-2022-41742).
</p></td></tr><tr><td class="date"><a name="2022-09-13"></a>2022-09-13</td><td><p><a href="https://unit.nginx.org/">unit-1.28.0</a> version has been
<a href="https://unit.nginx.org/news/2022/unit-1.28.0-released/">released</a>.
</p></td></tr><tr><td class="date"><a name="2022-08-30"></a>2022-08-30</td><td><p><a href="en/docs/njs/index.html">njs-0.7.7</a>
version has been
<a href="en/docs/njs/changes.html#njs0.7.7">released</a>,
featuring advanced
<a href="en/docs/njs/reference.html#njs_api_fs">fs</a> API and
<a href="en/docs/njs/changes.html#contexts">extended js directives scope</a>.
</p></td></tr><tr><td class="date"><a name="2022-07-19"></a>2022-07-19</td><td><p><a href="en/download.html">nginx-1.23.1</a>
mainline version has been released.
</p></td></tr>
            </table>
        </div></div></body></html>
