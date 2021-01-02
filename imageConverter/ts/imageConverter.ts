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
    public dropHandler: Function;
    public dragHandler: Function;
    public dragLeaveHandler: Function;

    private $btnAscii = <HTMLInputElement>document.getElementById('btnAscii');
    private $btnInput = document.createElement('input');
    private $btnInverting = <HTMLInputElement>document.getElementById('btnInverting');
    private $btnBinary = <HTMLInputElement>document.getElementById('binary');
    private $btnHex = <HTMLInputElement>document.getElementById('hex');
    private $btnThreshold = <HTMLInputElement>document.getElementById('btnThreshold');
    private $btnClipboard = <HTMLInputElement>document.getElementById('btnClipboard');
    private $txtCopied = <HTMLInputElement>document.getElementById('copied');
    private $dropArea = document.getElementById('dropArea');
    private $loadedImage = <HTMLImageElement>document.getElementById('loadedImage');
    private tempCanvas = document.createElement('canvas');
    private $imageName = document.getElementById('imageName');
    private $imageSize = document.getElementById('imageSize');
    private $imageDimension = document.getElementById('imageDimension');
    private $imageAspectRatio = document.getElementById('aspect');
    private $fileType = document.getElementById('fileType');
    private $code = <HTMLDivElement>document.getElementById('code');
    private $preview = <HTMLCanvasElement>document.getElementById('previewImage');
    private fileReader = new FileReader();
    private file: File;

    constructor() {
        this.init();
    }

    private init(){
        this.$btnInput.type = 'file';
        this.$btnInput.multiple = true;

        // Register event handlers
        this.$dropArea.addEventListener('click', () => {
            this.onClickUpload();
        });

        this.$btnClipboard.addEventListener('click', () => {
            this.onClickClipboard();
        });

        this.$btnInput.onchange = () => {
            this.onFileSelection();
        };

        this.$btnInverting.onchange = () => {
            this.refresh();
        };

        this.$btnHex.onchange = () => {
            this.refresh();
        };

        this.$btnAscii.onchange = () => {
            this.refresh();
        };

        this.$btnBinary.onchange = () => {
            this.refresh();
        };

        this.$btnThreshold.onchange = () => {
            this.refresh();
        };

        this.$loadedImage.onload = () => {
            this.refresh();
        };

        this.fileReader.onload = () => {
            // We use filereader readAsDataURL, so result is a string
            this.$loadedImage.src = <string>this.fileReader.result;
        }

        this.dropHandler = this.onDropFile;
        this.dragHandler = this.onDrag;
        this.dragLeaveHandler = this.onDragLeave;
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

        this.file = selectedFile;
        this.fileReader.readAsDataURL(selectedFile);
    }

    private refresh() {
        if(!this.file){ return; }

        // Trigger visibility of loaded image.
        this.$loadedImage.style.display = 'block';

        // Render meta data of loaded image.
        const imageDimension = {
            width: this.$loadedImage.naturalWidth,
            height: this.$loadedImage.naturalHeight
        }

        this.$imageName.innerText = this.file.name;
        this.$imageSize.innerText = `Filesize: ${this.file.size} Bytes`;
        this.$imageDimension.innerText = `Width: ${imageDimension.width}px / Height: ${imageDimension.height}px`;
        this.$imageAspectRatio.innerText = `Aspect Ratio: ${(imageDimension.width / imageDimension.height).toFixed(2)}`;
        this.$fileType.innerText = `File type: ${this.file.type}`;

        // Decode image pixel data
        this.tempCanvas.width = imageDimension.width;
        this.tempCanvas.height = imageDimension.height;
        const tempContext = this.tempCanvas.getContext('2d');
        tempContext.clearRect(0, 0, this.tempCanvas.width, this.tempCanvas.height);
        tempContext.drawImage(this.$loadedImage, 0, 0);
        const pixeldata = tempContext.getImageData(0, 0, imageDimension.width, imageDimension.height);
        
        // Render output
        const code = this.getCode(ConverterMode.OneBit, pixeldata.data);
        this.renderPreview(code);
        this.$code.innerText = this.generateProgramCode(code);
    }

    /**
     * Generates a string containing decoded pixel data as 
     * bitmask and optional ascii art.
     * @param mode The code generation mode. Default is 1 Bit.
     */
    private getCode(mode=ConverterMode.OneBit, pixelData: Uint8ClampedArray): string {
        let code = '';

        switch (mode) {
            case ConverterMode.OneBit:
                code = this.convertToOneBit(pixelData);
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

    private convertToOneBit(pixelData: Uint8ClampedArray): string {
        let code = '';
        const outPutFormat = this.$btnHex.checked ? OutputFormat.Hexadecimal : OutputFormat.Binary;
        const settings: ConverterSettings = {
            asciiArt: true,
            asciiCharacter: '*',
            invert: this.$btnInverting.checked,
            format: outPutFormat,
            imageType: this.file.type,
            pixelData: pixelData
        };
        let bitOn = settings.invert ? '0' : '1';
        let bitOff = (1 - parseInt(bitOn, 2)).toString();
        const pixelSize = 4;
        const data: Uint8ClampedArray = settings.pixelData;
        const imageWidth = this.tempCanvas.width;

        for (let index = 0, red, green, blue, alpha; index < data.length; index += pixelSize) {
            [red, green, blue, alpha] = data.slice(index, index + pixelSize);
            
            /*const pixelSum = red + green + blue + alpha;
            code += pixelSum === 255 ? bitOff : bitOn;*/
            
            const pixelSum = red + green + blue;
            const threshold = parseInt(this.$btnThreshold.value, 10);
            code += pixelSum / 3 >= threshold ? bitOn : bitOff;

            if((index + pixelSize) % (imageWidth * pixelSize) === 0) {
                code += '\n';
            }
        }
        code += '\n';

        return code;
    }

    private onDropFile(event: DragEvent) {
        event.preventDefault();

        this.file = event.dataTransfer.files[0];
        this.fileReader.readAsDataURL(this.file);
    }

    private onDrag(event: DragEvent) {
        event.preventDefault();
        this.$dropArea.setAttribute('dragging', 'true');
    }

    private onDragLeave(event: DragEvent) {
        event.preventDefault();
        this.$dropArea.removeAttribute('dragging');
    }

    private generateProgramCode(code: string): string {
        const rows = code.split('\n');
        const ascii = this.$btnAscii.checked;
        const width = this.tempCanvas.width;
        const height = this.tempCanvas.height;
        const outPutFormat = this.$btnHex.checked ? OutputFormat.Hexadecimal : OutputFormat.Binary;
        let asciiArt = Array<String>();

        // Generate ASCII Art for each row of pixels
        if(ascii) {
            rows.forEach(row => {
                asciiArt.push(this.createAsciiArt(row));
            });
        }

        // Generate code output
        code = code.replaceAll('\n', '');
        let generatedProgramCode = `\{\n${width}, ${height},\n`;
        let byte2dArray = [];

        for (let y = 0; y < width * height; y += width) {
            let row = [];
            const rowEnd = y + width;
            let x = y;
            while (x < rowEnd) {
                const length = Math.min(rowEnd - x, 8);
                let bytePiece = code.substr(x, length);
                bytePiece = bytePiece.padEnd(8, "0");
                if(outPutFormat === OutputFormat.Hexadecimal){
                    bytePiece = parseInt(bytePiece, 2)
                        .toString(16)
                        .toUpperCase()
                        .padStart(2, '0');
                    row.push(`0x${bytePiece}`);
                } else {
                    row.push(`B${bytePiece}`);
                }
                
                x += 8;
            }
            byte2dArray.push(row);
        }

        // Convert 2d array to desired string
        byte2dArray = byte2dArray.map(row => row.join(", "));
        let byteArrayAsString = '';
        if(!this.$btnAscii.checked) {
            byteArrayAsString = byte2dArray.join(',\n');
            byteArrayAsString += '\n';
        } else {
            // Append ASCII art
            for (let index = 0; index < height; index++) {
                if(index != height-1){
                    byteArrayAsString += `${byte2dArray[index]},${asciiArt[index]}`;
                } else {
                    byteArrayAsString += `${byte2dArray[index]} ${asciiArt[index]}`;
                }
            }
        }
        generatedProgramCode += `${byteArrayAsString}};`

        return generatedProgramCode;
    }

    private onClickClipboard(): void {
        const fakeInput = document.createElement('textarea');
        this.$txtCopied.style.opacity = '1.0';
        this.$txtCopied.style.transition = 'none';
        setTimeout(() => {
            this.$txtCopied.style.opacity = '0.0';
            this.$txtCopied.style.transition = 'opacity 3s';
        }, 2500);
        document.body.appendChild(fakeInput);
        fakeInput.value = this.$code.innerText;
        fakeInput.select();
        fakeInput.setSelectionRange(0, 99999);
        document.execCommand('copy');
        fakeInput.style.visibility = 'hidden';
    }

    private createAsciiArt(row: string): string {
        row = row.replaceAll('0', '◻');
        row = row.replaceAll('1', '◼');
        row = ` // ${row}\n`;

        return row;
    }
}