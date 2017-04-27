#include "cap_detection.cpp"
#include "header.h"
#include "video-frames.cpp"

string masterproject::siddiqui =
    "/Users/siddiqui/Documents/Projects/master-project/meetings/";
string masterproject::umair = "/Users/Umair/Desktop/master-project/meetings/";
string masterproject::rizwan = "Undefined (No User Found)";
string masterproject::cwd = masterproject::siddiqui;

void fetchImagesFromFolder(vector<Mat>& data, const string path) {
  vector<String> fn;
  glob(path, fn, true);  // recurse
  for (size_t k = 0; k < fn.size(); ++k) {
    cv::Mat im = cv::imread(fn[k]);
    if (im.empty()) continue;  // only proceed if sucsessful
    data.push_back(im);
  }
}

int main() {
  bool BY_REFERENCE = true;
  bool SAVE_RESULTS = true;
  vector<Mat> images;
  fetchImagesFromFolder(images, masterproject::cwd + "meeting-12/lower/");
  for (auto& inputImage : images) {
    Size s1 = inputImage.size();
    BottleDetection regionOfInterest(inputImage);
    // remove the edges of the image before applying the algorithms
    regionOfInterest.getRegionOfInterest(
        inputImage,      // image
        s1.width / 7,    // remove 1/7th from left
        s1.height / 10,  // remove 1/10th from top
        s1.width - (2 * s1.width / 7), s1.height - s1.height / 10);
    Mat capData, blobData;
    if (BY_REFERENCE == true) {
      capData = inputImage;
      blobData = inputImage;
    } else if (BY_REFERENCE == false) {
      inputImage.copyTo(capData);
      inputImage.copyTo(blobData);
    }

    CapDetection detectCaps(capData, 45, 65);
    BottleDetection detectBottles(blobData);

    // detect caps of the bottle
    detectCaps.getCaps();
    // detect presence of the bottle
    detectBottles.getBottles();
    // detect dark bottles
    detectBottles.getDarkBottles();

    if (BY_REFERENCE == true) {
        imshow("results: ", inputImage);
      if (SAVE_RESULTS)
        ::saveImage(masterproject::cwd + "/meeting-12/results/result.bmp",
                    inputImage);
    } else if (BY_REFERENCE == false) {
      Mat result;
      vconcat(blobData, capData, result);
      hconcat(blobData, capData, result);
      if (SAVE_RESULTS)
        ::saveImage(masterproject::cwd + "/meeting-12/results/result.bmp",
                    result);
      imshow("results: ", result);
    }
    waitKey(1);
  }

  return 0;
}
