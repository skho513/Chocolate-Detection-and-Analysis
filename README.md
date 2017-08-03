# Chocolate-Detection-and-Analysis

In General:
Compile the code using “cmake .” and “make” commands, then run it by typing ./DisplayImage chocolate_eggs size_sort (The program does NOT run if you only input one image, and in wrong order). This does the loading the source image. 

2. Object detection and sorting by color 
Description:
Inside the program, the cvtColor() method is used to convert it from BGR to HSV format, because in HSV, it is more easier to represent a color than in BGR color space. The source image is then smoothed out by blurring and denoising applied by the median filter. Threshold the HSV image for a range of colors, so we store each specific color’s pixel values. In our case, they are red, green, white, yellow and blue. Gaussian filter is used to blur the extracted color image for a refining purpose. 
Pass all the colored images to the drawCircles() method. In this method, the HoughCircles() method is used to draw matching colored circles on those of the same colored chocolates. This is also used, because chocolates resemble circle-like shape, making them easily detectable. All the circles are stored in the circles vector, and the detected circles are outlined on the chocolates of appropriate colors. On the original image, red circles are drawn first, then passed on to the next HoughCircles transform to draw green circles on the original image with the red circles added, then gets passed on to the next color. In each round of HoughCircles transform, text output of the number of circles drawn is printed. After all the circles are drawn, the image with all the colored circles is saved as JPG image in the current directory as “chocolate_eggs_marked.jpg”.

3. Sorting objects by size
Description: Image is loaded and read from second argument. Its BGR format is converted into greyscale for the thresholding purpose. Blurring is also done to make the object detection easily. Then edges of the objects are detected by thresholding. The contours; a line joining each point of the edge are found from the objects. The minimum area of the rectangles are applied to enclose the objects, and the rectangles are drawn. The image size_sort.jpg is of pixel size 3000X2000. This means the size of the 15mm is equivalent to 100pixels (3000X15/450). Therefore any eggs below 100pixels are bad eggs and the rest of the detected eggs are good.
