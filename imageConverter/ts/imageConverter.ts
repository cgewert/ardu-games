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

const enum ConverterMode {
    OneBit,
}

const enum OutputFormat {
    Binary,
    Hexadecimal
}


interface ConverterSettings {
    invert: boolean;
    asciiArt: boolean;
    asciiCharacter: string;
    format?: OutputFormat;
    imageType: string;
    pixelData: Uint8ClampedArray;
}

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
    private $preview = <HTMLCanvasElement>document.getElementById('previewImage');
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
        // Trigger visibility of loaded image.
        this.$loadedImage.style.display = 'block';

        // Render meta data of loaded image.
        const file = this.$btnInput.files[0];
        const imageDimension = {
            width: this.$loadedImage.naturalWidth,
            height: this.$loadedImage.naturalHeight
        }

        this.$imageName.innerText = file.name;
        this.$imageSize.innerText = `Filesize: ${file.size} Bytes`;
        this.$imageDimension.innerText = `Width: ${imageDimension.width}px / Height: ${imageDimension.height}px`;
        this.$imageAspectRatio.innerText = `Aspect Ratio: ${(imageDimension.width / imageDimension.height).toFixed(2)}`;
        this.$fileType.innerText = `File type: ${file.type}`;

        // Decode image pixel data
        this.tempCanvas.width = imageDimension.width;
        this.tempCanvas.height = imageDimension.height;
        const tempContext = this.tempCanvas.getContext('2d');
        tempContext.clearRect(0, 0, this.tempCanvas.width, this.tempCanvas.height);
        tempContext.drawImage(this.$loadedImage, 0, 0);
        const pixeldata = tempContext.getImageData(0, 0, imageDimension.width, imageDimension.height);
        
        // Render output
        const code = this.getCode(ConverterMode.OneBit, pixeldata.data);
        this.$code.innerText = code;
        this.renderPreview(code);
    }

    /**
     * Generates a string containing decoded pixel data as 
     * bitmask and optional ascii art.
     * @param mode The code generation mode. Default is 1 Bit.
     */
    private getCode(mode=ConverterMode.OneBit, pixelData: Uint8ClampedArray): string {
        let code = '';
        const settings: ConverterSettings = {
            asciiArt: true,
            asciiCharacter: '*',
            invert: true,
            format: OutputFormat.Binary,
            imageType: this.$btnInput.files[0].type,
            pixelData: pixelData
        };

        switch (mode) {
            case ConverterMode.OneBit:
                code = this.convertToOneBit(settings);
                break;
            default:
                break;
        }

        return code;
    }

    /**
     * Renders the generated image in the preview canvas.
     * @param code The bitmap string.
     */
    private renderPreview(code: string): void {
        this.$preview.width = this.tempCanvas.width;
        this.$preview.height = this.tempCanvas.height;
        const context = this.$preview.getContext('2d');
        let imageData = [];

        for(let index = 0; index < code.length; index++) {
            if(!code[index].match('[10]')){
                continue
            };

            const pixel = code[index] === '1' ? [255, 255, 255, 255] : [0, 0, 0, 255];
            imageData.push(...pixel);
        }
        
        let imageDataUint8 = new Uint8ClampedArray(imageData);
        context.putImageData(new ImageData(imageDataUint8, this.tempCanvas.width, this.tempCanvas.height), 0, 0);
    }

    private convertToOneBit(settings: ConverterSettings): string {
        let code = '';
        let bitOn = settings.invert ? '0' : '1';
        let bitOff = (1 - parseInt(bitOn, 2)).toString();
        const pixelSize = 4;
        const data: Uint8ClampedArray = settings.pixelData;
        const imageWidth = this.tempCanvas.width;

        for (let index = 0, red, green, blue, alpha; index < data.length; index += pixelSize) {
            // @ts-ignore
            [red, green, blue, alpha] = data.slice(index, index + pixelSize);
            
            const pixelSum = red + green + blue + alpha;

            code += pixelSum === 255 ? bitOff : bitOn;
            if((index + pixelSize) % (imageWidth * pixelSize) === 0) {
                code += '\n';
            }
        }
        code += '\n';

        return code;
    }
}