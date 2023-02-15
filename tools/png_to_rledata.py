from PIL import Image

# need to parse command line to get filePath and varName
# need option to output binary data instead of C source

filePath = "../assets/dragon_test/dragon_test_512x256.png"
varName = "dragon_test"


def encodeRow(im: Image, y: int):
    rleData = []
    runColor = None
    runLength = None
    for x in range(im.width):    
        color = im.getpixel((x, y))
        if color != runColor:
            if runColor != None:
                rleData.append((runLength, runColor))
            runColor = color
            runLength = 1
        else:
            runLength = runLength + 1
    rleData.append((runLength, runColor))
    return rleData

im = Image.open(filePath)
print("const char %s[] = {" % varName)
byteCount = 0
for rowNum in range(im.height):
    rleData = encodeRow(im, rowNum)
    byteCount = byteCount + 1 + len(rleData) * 2
    print("    %d, " % len(rleData), end="")
    for datum in rleData:
        print("%d,%d, " % datum, end="")
    print()
print("};")
print("int %s_len = %d;" % (varName, byteCount))