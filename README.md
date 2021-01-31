# Matrix_CNN

Description:  
    The main goal of the task is to implement the application, 
    performing the convolution operation on the input data. 
    With the current implementation can be performed the convolution
    operation on the given matrix with the provided filter and store 
    the output matrix into the output file.

Inputs:
    Inputs - the input is the matrix of size [1 x 32 x 32].
    It must be possible to provide more that one input matrix.
    The input (s) must be read from file. 
    Filter the matrix of size [1 x 5 x 5].
    it must be possible to change the filter and apply different filters on the same input matrix.
    it must be possible to implement multiple filters on the same input data.
    the filter (s) must be specified in the file, read by application .
    Biases - single bias value is used for each filter. 

Output:
    the result of the operation is a matrix of the dimension: [1 x 28 x 28]
    The output must be dumped into the result file

Language Requirements:
    Implementation is in C++

How exactly does the Convolution Operation work?
    You can think of the feature detector as a window consisting of 9 (3×3) cells. Here is what you do with it:

   * You place it over the input image beginning from the top-left corner within the borders you see demarcated above,
    and then you count the number of cells in which the feature detector matches the input image.
    The number of matching cells is then inserted in the top-left cell of the feature map.
        --carried out using the getBlockAt() function:

   * You then move the feature detector one cell to the right and do the same thing.
    This movement is called a and since we are moving the feature detector one cell at time,
    that would be called a stride of one pixel.

   * What you will find in this example is that the feature detector's middle-left 
    cell with the number 1 inside it matches the cell that it is standing over inside the input image.
    That's the only matching cell, and so you write “1” in the next cell in the feature map, and so on and so forth.

   * After you have gone through the whole first row, you can then move it over to the next row and go through the same process.
        --These three points are done using the dotProduct() and doCNN() functions

    It's important not to confuse the feature map with the other two elements.
    The cells of the feature map can contain any digit, not only 1's and 0's.
    By the way, just like feature detector can also be referred to as a kernel or a filter,
    a feature map is also known as an activation map and both terms are also interchangeable.
