
// CS112_A3_Part2B_S8_20230024_20230036_20230731.cpp
//
// Purpose : Mini photoshop meant ot take an image file and apply a filter to it
//
//  Last Modification Date: 15/4/2024
//
//  Author1 and ID : Ahmed mostafa ,20230036 ,mosatufaa@gmail.com
// finished filters: blur,resize,add frame,crop,rotate, infrared vision,merge
//
//  Author2 and ID : Ahmed Tarek Hassan,20230024,at012306@gmail.com
// Finished filters: greyscale,darken/lighten,detect edges,night vision,  black and white
//
//  Author3 and ID : Albaraa Musab Ali,20230731,albaraamusabali@gmail.com
// saveimg,loadimg,invert image,flip image,sunlight
//
// github link:https://github.com/albaraa-ali/assignment-3

// include the necessary header files and libaries
#include "Image_Class.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// function to create an empty file with the name from the user's choice and
// saves it to the memory
void saveimg() {

  string filename;
  Image image;
  cout << "Please enter the image name to store the new image" << endl;
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  while (true) {
    try {
      cin >> filename;
      image.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// function to load an image from the memory only if the file exists
void loadimg() {
  string filename;
  Image image;
  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// function to take an image from the memory, turn it into grayscale and save it
// to the memory with the name the user chooses
void greyscale() {
  string filename;
  unsigned int avg;
  Image image;
  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }

  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      avg = 0;
      for (int k = 0; k < image.channels; ++k) {
        avg += image(i, j, k);
      }
      avg /= image.channels;
      for (int k = 0; k < image.channels; ++k) {
        image(i, j, k) = avg;
      }
    }
  }

  cout << "Please enter the image name to store the new grayscale image"
       << endl;
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  while (true) {
    try {
      cin >> filename;
      image.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// function to take an image from the memory, turn it into black and white and
// save it to the memory with the name the user chooses
void blackAndWhite() {
  string filename;
  unsigned int avg = 0;
  Image image;
  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }

  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      for (int k = 0; k < image.channels; ++k) {
        avg += image(i, j, k);
      }
      avg /= image.channels;
      if (avg < 128) {
        for (int k = 0; k < image.channels; ++k) {
          image(i, j, k) = 0;
        }
      } else {
        for (int k = 0; k < image.channels; ++k) {
          image(i, j, k) = 255;
        }
      }
    }
  }

  cout << "Pls enter image name to store new image" << endl;
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  while (true) {
    try {
      cin >> filename;
      image.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// function to take an image from the memory, turn it into negative colors and
// save it to the memory with the name the user chooses
void invertImage() {
  string filename;
  Image image;
  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }

  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      for (int k = 0; k < image.channels; ++k) {
        image(i, j, k) = 255 - image(i, j, k);
      }
    }
  }

  cout << "Pls enter image name to store new image" << endl;
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  while (true) {
    try {
      cin >> filename;
      image.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// function to take two images, overlap them and save the result to the memory
// with the name the user chooses. if the images are not the same size, only the
// part of the first image that fits in the second one will be overlapped
void mergeImages() {
  string filename;
  Image image1;
  Image image2;
  cout << "Please enter the name of the first image: " << endl;
  while (true) {
    cin >> filename;
    try {
      image1 = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
  cout << "Please enter the name of the second image: " << endl;
  while (true) {
    cin >> filename;
    try {
      image2 = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }

  int mergedwidth = min(image1.width, image2.width);
  int mergedheight = min(image1.height, image2.height);
  Image mergedimage(mergedwidth, mergedheight);

  // Merge images
  for (int i = 0; i < mergedwidth; ++i) {
    for (int j = 0; j < mergedheight; ++j) {
      for (int k = 0; k < mergedimage.channels; ++k) {
        // Calculate average pixel value
        mergedimage(i, j, k) =
            (image1.getPixel(i, j, k) + image2.getPixel(i, j, k)) / 2;
      }
    }
  }

  cout << "Please enter a filename for the merged image" << endl;
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  while (true) {
    cin >> filename;
    try {
      mergedimage.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// function to take an image from the memory, flip it vertically or horizontally
// and save it to the memory with the name the user chooses
void flipImage() {
  string filename;
  char choice;
  Image image;
  Image flippedimage;
  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      flippedimage = Image(image.width, image.height);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
  cout << "Choose whether you want to flip vertically(v) or horizontally(h): "
       << endl;
  while (true) {
    try {
      cin >> choice;
      if (choice == 'h' || choice == 'H') {
        for (int i = 0; i < image.width; ++i) {
          for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
              flippedimage(i, j, 0) = image(image.width - i - 1, j, 0);
              flippedimage(i, j, 1) = image(image.width - i - 1, j, 1);
              flippedimage(i, j, 2) = image(image.width - i - 1, j, 2);
            }
          }
        }
      } else if (choice == 'v' || choice == 'V') {
        for (int i = 0; i < image.width; ++i) {
          for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
              flippedimage(i, j, 0) = image(i, image.height - j - 1, 0);
              flippedimage(i, j, 1) = image(i, image.height - j - 1, 1);
              flippedimage(i, j, 2) = image(i, image.height - j - 1, 2);
            }
          }
        }
      } else {
        cout << "invalid input" << endl;
        continue;
      }
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid choice. Please try again." << endl;
      continue;
    }
  }

  cout << "Pls enter image name to store new image" << endl;
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  while (true) {
    try {
      cin >> filename;
      flippedimage.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// function to take an image from the memory, rotate it 90, 180, or 270 degrees
// clockwise and save it to the memory with the name the user chooses
void rotateImage() {
  string filename;
  int angle;
  Image image;
  cout << "Pls enter image name to rotate: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
  Image rotatedimage = image;
  cout << "Choose the rotation angle (1=>90, 2=>180, 3=>270): " << endl;
  while (true) {
    try {
      cin >> angle;
      switch (angle) {
      case 1:
        rotatedimage = Image(image.height, image.width);
        for (int i = 0; i < image.width; ++i) {
          for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
              rotatedimage(image.height - j - 1, i, k) = image(i, j, k);
            }
          }
        }
        break;
      case 2:
        rotatedimage = Image(image.width, image.height);
        for (int i = 0; i < image.width; ++i) {
          for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
              rotatedimage(image.width - i - 1, image.height - j - 1, k) =
                  image(i, j, k);
            }
          }
        }
        break;
      case 3:
        rotatedimage = Image(image.height, image.width);
        for (int i = 0; i < image.width; ++i) {
          for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
              rotatedimage(j, image.width - i - 1, k) = image(i, j, k);
            }
          }
        }
        break;
      default:
        cout << "invalid input" << endl;
        return;
      }
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid angle. Please try again." << endl;
      continue;
    }
  }

  cout << "Pls enter image name to store new image" << endl;
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  while (true) {
    try {
      cin >> filename;
      rotatedimage.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// function to take an image from the memory and either darken or lighten it by
// 50%. then it saves it to the memory with the name the user chooses
void changeLighting() {
  string filename;
  char choice;
  int newvalue;
  Image image;
  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
  cout << "Choose whether you want to darken (d) or lighten (l) the image: "
       << endl;
  while (true) {
    try {
      cin >> choice;
      if (choice == 'd' || choice == 'D') {
        for (int i = 0; i < image.width; ++i) {
          for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
              image(i, j, k) /= 2;
            }
          }
        }
      } else if (choice == 'l' || choice == 'L') {
        for (int i = 0; i < image.width; ++i) {
          for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
              newvalue = image(i, j, k) * 1.5;
              image(i, j, k) = min(newvalue, 255);
            }
          }
        }
      } else {
        cout << "invalid input" << endl;
        continue;
      }
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid choice. Please try again." << endl;
      continue;
    }
  }

  cout << "Pls enter image name to store new image" << endl;
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  while (true) {
    try {
      cin >> filename;
      image.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// function to take an image from the memory and take a starting point.from
// there it crops a specific area and then it saves the image to the memory with
// the name the user chooses
void cropImage() {
  int x, y, w, h;
  string filename, coordinates, dimensions;
  Image image;
  char comma;
  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }

  cout << "Enter the coordinates of your starting point (x, y): ";
  while (true) {
    try {
      cin >> coordinates;
      istringstream iss(coordinates);
      iss >> x >> comma >> y;

      if (!(0 < x && x <= image.width) || !(0 < y && y <= image.height)) {
        cout << "The point cannot be outside of the picture." << endl;
        continue;
      }
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid coordinates. Please try again." << endl;
      continue;
    }
  }

  cout << "Enter the dimensions of your cropped image (width, height): ";
  while (true) {
    try {
      cin >> dimensions;
      istringstream iss_dim(dimensions);
      iss_dim >> w >> comma >> h;

      if (x + w > image.width || y + h > image.height) {
        cout << "The cropped image cannot be bigger than the original." << endl;
        continue;
      }
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid dimensions. Please try again." << endl;
      continue;
    }
  }

  Image cropped(w, h);
  for (int i = x; i < x + w; ++i) {
    for (int j = y; j < y + h; ++j) {
      for (int k = 0; k < image.channels; ++k) {
        cropped(i - x, j - y, k) = image(i, j, k);
      }
    }
  }

  cout << "Enter the name of the save image: ";
  while (true) {
    try {
      cin >> filename;
      cropped.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// fuction to take an image from the user and put it inside a frame with the
// color of the user's choice
void addFrame() {
  const double FRAME_RATIO = 0.1;
  string filename;
  int choice;
  char choice2;

  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      Image image(filename);
      int frameWidth = min(image.width, image.height) * FRAME_RATIO;
      Image framed(image.width + frameWidth, image.height + frameWidth);

      cout << "Choose the frame color:" << endl;
      cout << "1. Red" << endl;
      cout << "2. Silver" << endl;
      cout << "3. Gold" << endl;
      cin >> choice;

      switch (choice) {
      case 1:
        for (int i = 0; i < framed.width; ++i) {
          for (int j = 0; j < framed.height; ++j) {
            framed(i, j, 0) = 255;
            framed(i, j, 1) = 0;
            framed(i, j, 2) = 0;
          }
        }
        break;
      case 2:
        for (int i = 0; i < framed.width; ++i) {
          for (int j = 0; j < framed.height; ++j) {
            framed(i, j, 0) = 150;
            framed(i, j, 1) = 150;
            framed(i, j, 2) = 180;
          }
        }
        break;
      case 3:
        for (int i = 0; i < framed.width; ++i) {
          for (int j = 0; j < framed.height; ++j) {
            framed(i, j, 0) = 255;
            framed(i, j, 1) = 220;
            framed(i, j, 2) = 0;
          }
        }
        break;
      default:
        cerr << "Invalid choice. Defaulting to Red." << endl;
        for (int i = 0; i < framed.width; ++i) {
          for (int j = 0; j < framed.height; ++j) {
            framed(i, j, 0) = 255;
            framed(i, j, 1) = 0;
            framed(i, j, 2) = 0;
          }
        }
      }

      cout << "Do you want to make it look fancy? (y/n): ";
      cin >> choice2;

      if (choice2 == 'y' || choice2 == 'Y') {
        int radius = frameWidth / 4;
        for (int x = radius; x < framed.width; x += 2 * radius) {
          for (int y = radius; y < framed.height; y += 2 * radius) {
            for (int i = -radius; i <= radius; ++i) {
              for (int j = -radius; j <= radius; ++j) {
                if (i * i + j * j <= radius * radius) {
                  if (x + i >= 0 && x + i < framed.width && y + j >= 0 &&
                      y + j < framed.height) {
                    framed(x + i, y + j, 0) = 255;
                    framed(x + i, y + j, 1) = 127;
                    framed(x + i, y + j, 2) = 0;
                  }
                }
              }
            }
          }
        }
      }

      else if (choice2 != 'n' && choice2 != 'N') {
        cerr << "Invalid input." << endl;
      }

      for (int i = frameWidth / 2; i < image.width + frameWidth / 2; ++i) {
        for (int j = frameWidth / 2; j < image.height + frameWidth / 2; ++j) {
          for (int k = 0; k < image.channels; ++k) {
            framed(i, j, k) =
                image(i - (frameWidth / 2), j - (frameWidth / 2), k);
          }
        }
      }

      cout << "Please enter a filename to store the new image "
              "with extension (.jpg, .bmp, .png, .tga): ";
      while (true) {
        try {
          cin >> filename;
          framed.saveImage(filename);
          cout << "Image saved successfully!" << endl;
          return; // Exit function after successful save
        } catch (const exception &e) {
          cerr << "Error: Invalid filename. Please try again." << endl;
        }
      }
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
    }
  }
}

void detectEdges() {
  string filename;
  Image image;
  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }

  // Convert the image to grayscale
  Image grayImage(image.width, image.height);
  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      int avg = 0;
      for (int k = 0; k < image.channels; ++k) {
        avg += image(i, j, k);
      }
      avg /= image.channels;
      grayImage(i, j, 0) = avg;
      grayImage(i, j, 1) = avg;
      grayImage(i, j, 2) = avg;
    }
  }

  // Detect edges using Sobel edge detection algorithm
  Image edgeImage(image.width, image.height);
  int sobel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  int sobel_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

  for (int i = 1; i < image.width - 1; ++i) {
    for (int j = 1; j < image.height - 1; ++j) {
      double gx = 0, gy = 0;
      for (int k = 0; k < 3; ++k) {
        for (int l = 0; l < 3; ++l) {
          gx += grayImage(i + k - 1, j + l - 1, 0) * sobel_x[k][l];
          gy += grayImage(i + k - 1, j + l - 1, 0) * sobel_y[k][l];
        }
      }
      double magnitude = sqrt(gx * gx + gy * gy);

      // Apply thresholding to obtain binary edge image
      edgeImage(i, j, 0) = (magnitude > 100) ? 0 : 255;
      edgeImage(i, j, 1) = (magnitude > 100) ? 0 : 255;
      edgeImage(i, j, 2) = (magnitude > 100) ? 0 : 255;
    }
  }

  cout << "Pls enter image name to store new image" << endl;
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  while (true) {
    try {
      cin >> filename;
      edgeImage.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// function to change the image dimensions based on the user's choice while
// maintaining the image content
void resizeImage() {
  int w, h;
  string filename, dimensions;
  Image image, resized;
  char comma;

  try {
    cout << "Please enter the image name: " << endl;
    cin >> filename;
    image = Image(filename);
  } catch (const exception &e) {
    cerr << "Error: Invalid filename. Please try again." << endl;
    return;
  }

  try {
    cout << "Enter the dimensions of your resized image (width, height): ";
    cin >> dimensions;
    istringstream iss_dim(dimensions);
    iss_dim >> w >> comma >> h;

    if (w <= 0 || h <= 0) {
      throw invalid_argument("Width and height must be positive numbers.");
    }
  } catch (const exception &e) {
    cerr << "Error: Invalid dimensions. Please try again." << endl;
    return;
  }

  resized = Image(w, h);
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      for (int k = 0; k < image.channels; ++k) {
        resized(i, j, k) = image(i * image.width / w, j * image.height / h, k);
      }
    }
  }

  try {
    cout << "Enter the name of the save image: ";
    cin >> filename;
    resized.saveImage(filename);
  } catch (const exception &e) {
    cerr << "Error: Invalid filename. Please try again." << endl;
    return;
  }
}

// function to blur an image and save it based on the user's choice
void blurImage() {
  const int BLOCK_SIZE = 30;
  const int BLOCK_PIXELS = BLOCK_SIZE * BLOCK_SIZE;
  string filename;
  Image image, blurred;

  // Input image name
  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: " << e.what() << ". Please try again." << endl;
    }
  }

  // Calculate adjusted dimensions based on the block size
  int adjustedWidth = image.width / BLOCK_SIZE * BLOCK_SIZE;
  int adjustedHeight = image.height / BLOCK_SIZE * BLOCK_SIZE;

  // Create a new image for the blurred result
  blurred = Image(adjustedWidth, adjustedHeight);

  // Apply blur
  for (int i = 0; i < adjustedWidth; i += BLOCK_SIZE) {
    for (int j = 0; j < adjustedHeight; j += BLOCK_SIZE) {
      for (int k = 0; k < image.channels; ++k) {
        int sum = 0;
        for (int x = i; x < i + BLOCK_SIZE; ++x) {
          for (int y = j; y < j + BLOCK_SIZE; ++y) {
            sum += image(x, y, k);
          }
        }
        int avg = sum / BLOCK_PIXELS;
        for (int x = i; x < i + BLOCK_SIZE; ++x) {
          for (int y = j; y < j + BLOCK_SIZE; ++y) {
            blurred(x, y, k) = avg;
          }
        }
      }
    }
  }

  // Save blurred image
  cout << "Please enter the image name to store the new image and specify "
          "extension (.jpg, .bmp, .png, .tga): ";
  while (true) {
    try {
      cin >> filename;
      blurred.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: " << e.what() << ". Please try again." << endl;
    }
  }
}

// function to apply a sepia filter to make the image look more yellow
void sunlight() {
  string filename;
  Image image;
  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }

  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      image(i, j, 2) *= 0.5;
    }
  }

  cout << "Pls enter image name to store new image" << endl;
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  while (true) {
    try {
      cin >> filename;
      image.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// function to apply a night effect to an image (colors in the night are purple)
void nightFilter() {
  string filename;
  Image image;
  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }

  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      image(i, j, 1) *= 0.6;
    }
  }

  cout << "Pls enter image name to store new image" << endl;
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  while (true) {
    try {
      cin >> filename;
      image.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// function to make the image look as if it's being viewed with infrared vision
void infraredvision() {
  string filename;
  Image image;
  cout << "Please enter the image name: " << endl;
  while (true) {
    try {
      cin >> filename;
      image = Image(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }

  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      image(i, j, 0) = 255;
      image(i, j, 1) = 255 - image(i, j, 1);
      image(i, j, 2) = 255 - image(i, j, 2);
    }
  }

  cout << "Pls enter image name to store new image" << endl;
  cout << "and specify extension .jpg, .bmp, .png, .tga: ";
  while (true) {
    try {
      cin >> filename;
      image.saveImage(filename);
      break;
    } catch (const exception &e) {
      cerr << "Error: Invalid filename. Please try again." << endl;
      continue;
    }
  }
}

// void to display the options of the filters
void displaymenu() {
  int choice;
  cout << "Choose the edit you want to apply" << endl;
  cout << "1. Greyscale" << endl;
  cout << "2. Black and White" << endl;
  cout << "3. Negative" << endl;
  cout << "4. Merge Images" << endl;
  cout << "5. Flip" << endl;
  cout << "6. Rotate" << endl;
  cout << "7. Change Lighting" << endl;
  cout << "8. Crop" << endl;
  cout << "9. Add Frame" << endl;
  cout << "10. Detect Edges" << endl;
  cout << "11. Resize Image" << endl;
  cout << "12. Blur" << endl;
  cout << "13. Add Sunlight" << endl;
  cout << "14. Night Filter" << endl;
  cout << "15. Infrared Vision" << endl;
  cout << "16. Exit" << endl;
  cin >> choice;

  switch (choice) {
  case 1:
    greyscale();
    break;
  case 2:
    blackAndWhite();
    break;
  case 3:
    invertImage();
    break;
  case 4:
    mergeImages();
    break;
  case 5:
    flipImage();
    break;
  case 6:
    rotateImage();
    break;
  case 7:
    changeLighting();
    break;
  case 8:
    cropImage();
    break;
  case 9:
    addFrame();
    break;
  case 10:
    detectEdges();
    break;
  case 11:
    resizeImage();
    break;
  case 12:
    blurImage();
    break;
  case 13:
    sunlight();
    break;
  case 14:
    nightFilter();
    break;
  case 15:
    infraredvision();
    break;
  case 16:
    exit(0);
  default:
    cout << "Invalid choice" << endl;
    break;
  }
}

// main menu
int main() {
  while (true) {
    cout << "1. save image" << endl;
    cout << "2. load image" << endl;
    cout << "3. edit image" << endl;
    cout << "4. exit" << endl;
    cout << "Please enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
      saveimg();
      break;
    case 2:
      loadimg();
      break;
    case 3:
      displaymenu();
      break;
    case 4:
      return 0;
    default:
      cerr << "Error: Invalid choice. Please try again." << endl;
      break;
    }
  }
}