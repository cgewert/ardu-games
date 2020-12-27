  /*class ImageConverter {
    $code = document.getElementById('code');
    $screen = document.getElementById('screen');
    $imageselect = document.getElementById('btnImageSelect');
    $imageWidth = document.getElementById('imagewidth'); 
    $imageHeight = document.getElementById('imageheight');
    $invertYes = document.getElementById('btnInvertYes');
    $invertNo = document.getElementById('btnInvertNo');
    $rowWidth = document.getElementById('num_blocks');
    
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
  
      $rowWidth.on("keyup input", function() {
        printBlocks = parseInt($numBlocks.value);
        doIt();
      });
  
      this.$imageselect.onchange = event => {
        let files = event.target.files;
        if (!files.length) {
            return;
        }
        
        let selectedFile = files[0];
        
        
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
      
      
      let uploadedImageSize = { 
          width: this.tempImg.width, 
          height: this.tempImg.height,
      };
    
      
      let tvOutImageWidth = 128;
      let tvOutImageHeight = 64;
      
      if (uploadedImageSize.width > tvOutImageWidth || uploadedImageSize.height > tvOutImageHeight) {
          let aspect = uploadedImageSize.width / uploadedImageSize.height;  // 1,25
          let targetAspect = tvOutImageWidth / tvOutImageHeight;            // 1,25
          let scaleAmount = 1;
          
          switch (this.scale) {
              case SCALES.FILL: 
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
                  break;
              default:
      
                  break;
          }
      
          uploadedImageSize.width = uploadedImageSize.width * scaleAmount;
          uploadedImageSize.height = uploadedImageSize.height * scaleAmount;
      }
      
      
      this.tempCanvas.width = 128;
      this.tempCanvas.height = 64;
      
      
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
          
          
          bitStr += this.factorFunc(r,g,b,a) ? bitOn : bitOff;
      }
      
      
      let byteArr = [];
      for (let i = 0; i < bitStr.length; i += 8) {
          byteArr.push(parseInt(bitStr.substring(i, i + 8), 2));
      }
    
      
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
      
      
      let visibleContext = this.$screen.getContext("2d");
      visibleContext.clearRect(0, 0, this.tempCanvas.width, this.tempCanvas.height);
      visibleContext.drawImage(this.tempImg, 0, 0, uploadedImageSize.width, uploadedImageSize.height);
    }
  }*/

class ImageConverter {
    private $btnInput = document.createElement('input');
    private $dragArea = document.getElementById('dragArea');
    private $loadedImage = <HTMLImageElement>document.getElementById('loadedImage');
    private tempCanvas = document.createElement('canvas');
    private $imageName = document.getElementById('imageName');
    private $imageSize = document.getElementById('imageSize');
    private $imageDimension = document.getElementById('imageDimension');
    private $imageAspectRatio = document.getElementById('aspect');
    private $fileType = document.getElementById('fileType');
    private $code = document.getElementById('code');
    private fileReader = new FileReader();

    constructor() {
        this.init();
    }

    private init(){
        this.$btnInput.type = 'file';
        this.$btnInput.multiple = true;

        // Register event handlers
        this.$dragArea.addEventListener('click', () => {
            this.onClickUpload();
        });

        this.$btnInput.onchange = event => {
            this.onFileSelection();
        };

        this.$loadedImage.onload = () => {
            this.refresh();
        };

        this.fileReader.onload = () => {
            // We use filereader readAsDataURL, so result is a string
            this.$loadedImage.src = <string>this.fileReader.result;
        }
    }

    private onClickUpload() {
        this.$btnInput.click();
    }

    private onFileSelection() {
        const files = this.$btnInput.files;
        const selectedFile = files[0] ? files[0] : false;
        
        if (!selectedFile || !selectedFile.type.match('image.*')) {
            console.log('No file or none image file selected!');

            return;
        }

        this.fileReader.readAsDataURL(selectedFile);
    }

    private refresh() {
        this.$loadedImage.style.display = 'block';
        const file = this.$btnInput.files[0];
        this.$imageName.innerText = file.name;
        this.$imageSize.innerText = `Filesize: ${file.size} Bytes`;
        const imageDimension = {
            x: this.$loadedImage.naturalWidth,
            y: this.$loadedImage.naturalHeight
        }
        this.$imageDimension.innerText = `Width: ${this.$loadedImage.naturalWidth}px / Height: ${this.$loadedImage.naturalHeight}px`;
        this.$imageAspectRatio.innerText = `Aspect Ratio: ${(imageDimension.x / imageDimension.y).toFixed(2)}`;
        this.$fileType.innerText = `File type: ${file.type}`;
        const tempContext = this.tempCanvas.getContext('2d');
        tempContext.clearRect(0, 0, this.tempCanvas.width, this.tempCanvas.height);
        tempContext.drawImage(this.$loadedImage, 0, 0);
        console.log(tempContext.getImageData(0, 0, imageDimension.x, imageDimension.y));
    }
}