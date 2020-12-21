Node.prototype.on = function(eventsStr, callback) {
  var eventNames = eventsStr.split(/\s+/);
  for (var i=0; i<eventNames.length; i++) {
      this.addEventListener(eventNames[i], callback);
  }
};

class ImageConverter {
  $code = document.getElementById('code');
  $screen = document.getElementById('screen');
  $imageselect = document.getElementById('btnImageSelect');
  $imageWidth = document.getElementById('imagewidth'); 
  $imageHeight = document.getElementById('imageheight');
  $invertYes = document.getElementById('btnInvertYes');
  $invertNo = document.getElementById('btnInvertNo');
  //$rowWidth = document.getElementById('num_blocks');
  
  inverting = false;
  scale = 1;
  rowWidth = 16;

  tempCanvas = document.createElement("canvas");
  tempImg = undefined;

  constructor() {
    this.$invertNo.on("click", () => {
      this.inverting = false;
      this.doIt();
    });

    this.$invertYes.on("click", () => {
      this.inverting = true;
      this.doIt();
    });

    /*$rowWidth.on("keyup input", function() {
      printBlocks = parseInt($numBlocks.value);
      doIt();
    });*/

    this.$imageselect.onchange = event => {
      let files = event.target.files;
      if (!files.length) {
          return;
      }
      
      let selectedFile = files[0];
      
      // Distinguish mime types and return if no image file was selected.
      if (!selectedFile.type.match('image.*')) {
          return;
      }
      
      let reader = new FileReader();
      reader.onload = () => {
          this.tempImg = document.createElement("img");
          this.tempImg.onload = () => {
              this.doIt();
          };
          this.tempImg.src = reader.result;
      };
      
      reader.readAsDataURL(selectedFile);
    };
  }

  factorFunc(r, g, b, a) {
    return (r + g + b + a === 1020)
  };

  doIt() {
    if (!this.tempImg) {
        return;
    }
    
    // Determine the target size, based on the scaling of the image.
    // Should be 120 width and 96 height
    let uploadedImageSize = { 
        width: this.tempImg.width, 
        height: this.tempImg.height,
    };
  
    // Static image resolution for Arduboy
    let tvOutImageWidth = 128;
    let tvOutImageHeight = 64;
    
    if (uploadedImageSize.width > tvOutImageWidth || uploadedImageSize.height > tvOutImageHeight) {
        //let aspect = uploadedImageSize.width / uploadedImageSize.height;  // 1,25
        //let targetAspect = tvOutImageWidth / tvOutImageHeight;            // 1,25
        let scaleAmount = 1;
        
        switch (this.scale) {
            /*case SCALES.FILL: 
                if (aspect < targetAspect) {
                    scaleAmount = tvOutImageWidth / uploadedImageSize.width;
                } else {
                    scaleAmount = tvOutImageHeight / uploadedImageSize.height;
                }
                break;
            case SCALES.FIT:
                if (aspect > targetAspect) {
                    scaleAmount = tvOutImageWidth / uploadedImageSize.width;
                } else {
                    scaleAmount = tvOutImageHeight / uploadedImageSize.height;
                }
                break;*/
            default:
                // Because we don't scale we should break here.
                break;
        }
    
        uploadedImageSize.width = uploadedImageSize.width * scaleAmount;
        uploadedImageSize.height = uploadedImageSize.height * scaleAmount;
    }
    
    // Pad the canvas size width to be a factor of 8 for rendering.
    this.tempCanvas.width = 128;
    this.tempCanvas.height = 64;
    
    // Now render the image onto another canvas so we can read back the pixel info.
    var tempContext = this.tempCanvas.getContext("2d");
    tempContext.clearRect(0, 0, this.tempCanvas.width, this.tempCanvas.height);
    tempContext.drawImage(this.tempImg, 0, 0, uploadedImageSize.width, uploadedImageSize.height);
    
    var imgData = tempContext.getImageData(0, 0, this.tempCanvas.width, this.tempCanvas.height);
    var imagePixels = imgData.data;
    
    let bitStr = ""; 
    let bitOn;
    let bitOff;
    
    if(this.invert === true){
        bitOn = "0";
        bitOff = "1";
    } else {
        bitOn = "1";
        bitOff = "0";
    }
  
    for (let i = 0, r, g, b, a; i < imagePixels.length; i += 4) {
        [r, g, b, a] = imagePixels.slice(i, i + 4);
        
        // Decide what we should do based on the factor and threshold.
        bitStr += this.factorFunc(r,g,b,a) ? bitOn : bitOff;
    }
    
    // The bytes are constructed in the y, not the x so transform them.
    let byteArr = [];
    for (let i = 0; i < bitStr.length; i += 8) {
        byteArr.push(parseInt(bitStr.substring(i, i + 8), 2));
    }
  
    // Now read the bits and render each block, of say 8, then do a new line.
    let codeStr = "";
    let hexStr = "";
    for (let i = 1; i <= byteArr.length; i++) {
        hexStr = byteArr[i-1].toString(16).padStart(2, "0").toUpperCase();
        codeStr += `0x${hexStr}, `;
        
        if (!(i % this.rowWidth)) {
            codeStr += "\n";
        }
    }
    
    codeStr = codeStr.substring(0, codeStr.length - 2);
    if (codeStr.length && codeStr[codeStr.length-1] == ",") {
        codeStr = codeStr.substring(0, codeStr.length - 1);
    }
    
    this.$code.value = `{${uploadedImageSize.width}, ${uploadedImageSize.height}, \n${codeStr}};`;
    
    this.$imageWidth.innerHTML = this.tempCanvas.width;
    this.$imageHeight.innerHTML = this.tempCanvas.height;
    
    // Draw the generated code to the real canvas element.
    let visibleContext = this.$screen.getContext("2d");
    visibleContext.clearRect(0, 0, this.tempCanvas.width, this.tempCanvas.height);
    visibleContext.drawImage(this.tempImg, 0, 0, uploadedImageSize.width, uploadedImageSize.height);
  }
}