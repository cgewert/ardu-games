# ImageConverter for Arduino

## Preconditions

Make sure to have node.js 12+ installed.

## Build and run

Install dependencies and build the application by running the following command in the source code root folder:

```sh
npm i && npm run build
```

The application will be build in the <b>/dist</b> folder and you can simply open the index.html in your browser to use it.

## Description

With this tool you can load PNG, GIF or JPEG image files and convert them to black and white bitmasks. These are generated as C source code and can be copied directly into your Arduino source code.  
<b>NOTE:</b>  
This tool targets small images (e.g. 16 * 16 or 128 * 64) you WILL experience performance issues when loading images with higher resolutions.
