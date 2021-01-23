var ConverterMode;
(function (ConverterMode) {
    ConverterMode[ConverterMode["OneBit"] = 0] = "OneBit";
})(ConverterMode || (ConverterMode = {}));
var OutputFormat;
(function (OutputFormat) {
    OutputFormat[OutputFormat["Binary"] = 0] = "Binary";
    OutputFormat[OutputFormat["Hexadecimal"] = 1] = "Hexadecimal";
})(OutputFormat || (OutputFormat = {}));
class ImageConverter {
    constructor() {
        this.$btnAscii = document.getElementById('btnAscii');
        this.$btnInput = document.createElement('input');
        this.$btnInverting = document.getElementById('btnInverting');
        this.$btnBinary = document.getElementById('binary');
        this.$btnHex = document.getElementById('hex');
        this.$btnThreshold = document.getElementById('btnThreshold');
        this.$btnClipboard = document.getElementById('btnClipboard');
        this.$inputIdentifier = document.getElementById('inputIdentifier');
        this.$txtCopied = document.getElementById('copied');
        this.$dropArea = document.getElementById('dropArea');
        this.$loadedImage = document.getElementById('loadedImage');
        this.tempCanvas = document.createElement('canvas');
        this.$imageName = document.getElementById('imageName');
        this.$imageSize = document.getElementById('imageSize');
        this.$imageWidth = document.getElementById('imageWidth');
        this.$imageHeight = document.getElementById('imageHeight');
        this.$imageAspectRatio = document.getElementById('aspect');
        this.$fileType = document.getElementById('fileType');
        this.$code = document.getElementById('code');
        this.$preview = document.getElementById('previewImage');
        this.fileReader = new FileReader();
        this.symbolDefinition = '';
        this.init();
    }
    init() {
        this.$btnInput.type = 'file';
        this.$btnInput.multiple = true;
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
        this.$inputIdentifier.onchange = () => {
            const csymbol = this.$inputIdentifier.value.trim();
            this.symbolDefinition = `const unsigned char ${csymbol}[] PROGMEM = `;
            this.refresh();
        };
        this.$loadedImage.onload = () => {
            this.refresh();
        };
        this.fileReader.onload = () => {
            this.$loadedImage.src = this.fileReader.result;
        };
        this.dropHandler = this.onDropFile;
        this.dragHandler = this.onDrag;
        this.dragLeaveHandler = this.onDragLeave;
    }
    onClickUpload() {
        this.$btnInput.click();
    }
    onFileSelection() {
        const files = this.$btnInput.files;
        const selectedFile = files[0] ? files[0] : false;
        if (!selectedFile || !selectedFile.type.match('image.*')) {
            console.log('No file or none image file selected!');
            return;
        }
        this.file = selectedFile;
        this.fileReader.readAsDataURL(selectedFile);
    }
    refresh() {
        if (!this.file) {
            return;
        }
        this.$loadedImage.style.display = 'block';
        const imageDimension = {
            width: this.$loadedImage.naturalWidth,
            height: this.$loadedImage.naturalHeight
        };
        this.$imageName.innerText = this.file.name;
        this.$imageSize.innerText = `Filesize: ${this.file.size} Bytes`;
        this.$imageWidth.innerText = `Width: ${imageDimension.width}px`;
        this.$imageHeight.innerText = `Height: ${imageDimension.height}px`;
        this.$imageAspectRatio.innerText = `Aspect Ratio: ${(imageDimension.width / imageDimension.height).toFixed(2)}`;
        this.$fileType.innerText = `File type: ${this.file.type}`;
        this.tempCanvas.width = imageDimension.width;
        this.tempCanvas.height = imageDimension.height;
        const tempContext = this.tempCanvas.getContext('2d');
        tempContext.clearRect(0, 0, this.tempCanvas.width, this.tempCanvas.height);
        tempContext.drawImage(this.$loadedImage, 0, 0);
        const pixeldata = tempContext.getImageData(0, 0, imageDimension.width, imageDimension.height);
        const code = this.getCode(0, pixeldata.data);
        this.renderPreview(code);
        this.$code.innerText = this.generateProgramCode(code);
    }
    getCode(mode = 0, pixelData) {
        let code = '';
        switch (mode) {
            case 0:
                code = this.convertToOneBit(pixelData);
                break;
            default:
                break;
        }
        return code;
    }
    renderPreview(code) {
        this.$preview.width = this.tempCanvas.width;
        this.$preview.height = this.tempCanvas.height;
        const context = this.$preview.getContext('2d');
        let imageData = [];
        for (let index = 0; index < code.length; index++) {
            if (!code[index].match('[10]')) {
                continue;
            }
            ;
            const pixel = code[index] === '1' ? [255, 255, 255, 255] : [0, 0, 0, 255];
            imageData.push(...pixel);
        }
        let imageDataUint8 = new Uint8ClampedArray(imageData);
        context.putImageData(new ImageData(imageDataUint8, this.tempCanvas.width, this.tempCanvas.height), 0, 0);
    }
    convertToOneBit(pixelData) {
        let code = '';
        const outPutFormat = this.$btnHex.checked ? 1 : 0;
        const settings = {
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
        const data = settings.pixelData;
        const imageWidth = this.tempCanvas.width;
        for (let index = 0, red, green, blue, alpha; index < data.length; index += pixelSize) {
            [red, green, blue, alpha] = data.slice(index, index + pixelSize);
            const pixelSum = red + green + blue;
            const threshold = parseInt(this.$btnThreshold.value, 10);
            code += pixelSum / 3 >= threshold ? bitOn : bitOff;
            if ((index + pixelSize) % (imageWidth * pixelSize) === 0) {
                code += '\n';
            }
        }
        code += '\n';
        return code;
    }
    onDropFile(event) {
        event.preventDefault();
        this.file = event.dataTransfer.files[0];
        this.fileReader.readAsDataURL(this.file);
    }
    onDrag(event) {
        event.preventDefault();
        this.$dropArea.setAttribute('dragging', 'true');
    }
    onDragLeave(event) {
        event.preventDefault();
        this.$dropArea.removeAttribute('dragging');
    }
    generateProgramCode(code) {
        const rows = code.split('\n');
        const ascii = this.$btnAscii.checked;
        const width = this.tempCanvas.width;
        const height = this.tempCanvas.height;
        const outPutFormat = this.$btnHex.checked ? 1 : 0;
        let asciiArt = Array();
        let generatedProgramCode = '';
        if (ascii) {
            rows.forEach(row => {
                asciiArt.push(this.createAsciiArt(row));
            });
        }
        code = code.replaceAll('\n', '');
        if (this.$inputIdentifier.value.trim()) {
            generatedProgramCode += this.symbolDefinition;
        }
        generatedProgramCode += `{\n${width}, ${height},\n`;
        let byte2dArray = [];
        for (let y = 0; y < width * height; y += width) {
            let row = [];
            const rowEnd = y + width;
            let x = y;
            while (x < rowEnd) {
                const length = Math.min(rowEnd - x, 8);
                let bytePiece = code.substr(x, length);
                bytePiece = bytePiece.padEnd(8, "0");
                if (outPutFormat === 1) {
                    bytePiece = parseInt(bytePiece, 2)
                        .toString(16)
                        .toUpperCase()
                        .padStart(2, '0');
                    row.push(`0x${bytePiece}`);
                }
                else {
                    row.push(`B${bytePiece}`);
                }
                x += 8;
            }
            byte2dArray.push(row);
        }
        byte2dArray = byte2dArray.map(row => row.join(", "));
        let byteArrayAsString = '';
        if (!this.$btnAscii.checked) {
            byteArrayAsString = byte2dArray.join(',\n');
            byteArrayAsString += '\n';
        }
        else {
            for (let index = 0; index < height; index++) {
                if (index != height - 1) {
                    byteArrayAsString += `${byte2dArray[index]},${asciiArt[index]}`;
                }
                else {
                    byteArrayAsString += `${byte2dArray[index]} ${asciiArt[index]}`;
                }
            }
        }
        generatedProgramCode += `${byteArrayAsString}};`;
        return generatedProgramCode;
    }
    onClickClipboard() {
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
        document.execCommand('copy');
        fakeInput.style.visibility = 'hidden';
    }
    createAsciiArt(row) {
        row = row.replaceAll('0', '◻');
        row = row.replaceAll('1', '◼');
        row = ` // ${row}\n`;
        return row;
    }
}
