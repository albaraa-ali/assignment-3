#include "Image_Class.h" // Assuming this header file contains the Image class definition
#include <iostream>
#include <string>

void menu() {
  std::cout << "1) Use App\n";
  std::cout << "2) Exit\n";
}

void displayMenu() {
  std::cout << "Menu:\n";
  std::cout << "1. Load a new image\n";
  std::cout << "2. Apply a filter on the current image\n";
  std::cout << "3. Store the image in a new or same file\n";
}

void filterOptions() {
  std::cout << "Filter Options:\n";
  std::cout << "1) Convert image to Black and White\n";
  std::cout << "2) Convert image to Gray scale\n";
}

void convertToBlackAndWhite(Image &image) {
  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      unsigned int avg = 0;

      for (int k = 0; k < 3; ++k) {
        avg += image(i, j, k);
      }

      avg /= 3;

      if (avg > 127.5) {
        image(i, j, 0) = 255;
        image(i, j, 1) = 255;
        image(i, j, 2) = 255;
      } else {
        image(i, j, 0) = 0;
        image(i, j, 1) = 0;
        image(i, j, 2) = 0;
      }
    }
  }
}

void convertToGrayScale(Image &image) {
  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      unsigned int avg = 0;

      for (int k = 0; k < 3; ++k) {
        avg += image(i, j, k);
      }

      avg /= 3;

      image(i, j, 0) = avg;
      image(i, j, 1) = avg;
      image(i, j, 2) = avg;
    }
  }
}

int main() {
  std::string option_1, option_2, option_filter;

  std::cout << "Hello User\n";
  while (option_1 != "2") {
    menu();
    std::getline(std::cin, option_1);

    if (option_1 == "2") {
      std::cout << "Have a Nice Day\n";
      break;
    }

    if (option_1 != "1") {
      std::cout << "Please enter a valid option\n";
      continue;
    }

    displayMenu();
    std::getline(std::cin, option_2);

    if (option_2 == "2") {
      filterOptions();
      std::getline(std::cin, option_filter);

      std::string filename;
      std::cout << "Enter the filename of the image: ";
      std::getline(std::cin, filename);

      Image image(filename);

      if (option_filter == "1") {
        convertToBlackAndWhite(image);
      } else if (option_filter == "2") {
        convertToGrayScale(image);
      } else {
        std::cout << "Invalid filter option\n";
        continue;
      }

      std::cout << "Enter the filename to store the new image (with extension "
                   ".jpg, .bmp, .png, .tga): ";
      std::getline(std::cin, filename);

      image.saveImage(filename);

      std::cout << "Image processed and saved successfully\n";
    }
  }

  return 0;
}
