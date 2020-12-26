const fs = require('fs');

fs.copyFileSync('index.html', 'dist/index.html');
fs.copyFileSync('assets/upload.svg', 'dist/upload.svg');