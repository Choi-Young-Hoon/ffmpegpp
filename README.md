# ffmpegpp
ffmpeg 6.1 c++ wrapper<br>
linux, windows support

<h1> Build </h1>
<pre>$ cmake .</pre>
<pre>$ make -j10</pre>
<pre>$ make install</pre>

<h2> Install vcpkg </h2>
<pre> <a href="https://vcpkg.io/en/">https://vcpkg.io/en/</a></pre>

<h2> Windows Build </h2>
<h3> - Install package </h3>
<pre> $ vcpkg install ffmpeg[fdk-aac,fontconfig,freetype,fribidi,gpl,mp3lame,nvcodec,vorbis,vpx,webp,x264,x265]:x64-windows gtest:x64-windows </pre>

<h2> Linux Build </h2>
<h3> - Install package </h3>
<pre> $ ./vcpkg install ffmpeg[fdk-aac,fontconfig,freetype,fribidi,gpl,mp3lame,nvcodec,vorbis,vpx,webp,x264,x265]:x64-linux gtest:x64-linux </pre>

