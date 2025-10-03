#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <sl/Camera.hpp>

using namespace std;
using namespace sl;

int main(int argc, char** argv)
{
    // Create a ZED camera object
    Camera zed;

    // Set configuration parameters
    InitParameters init_parameters;
    init_parameters.camera_resolution = RESOLUTION::AUTO; // Use HD720 opr HD1200 video mode, depending on camera type.
    init_parameters.camera_fps = 30; // Set fps at 30

    // Open the camera
    auto returned_state = zed.open(init_parameters);
    if (returned_state != ERROR_CODE::SUCCESS)
    {
        cout << "Error " << returned_state << ", exit program." << endl;
        return EXIT_FAILURE;
    }

    sl::Mat zedImage;

    while (true)
    {
        if (zed.grab() == sl::ERROR_CODE::SUCCESS)
        {
            zed.retrieveImage(zedImage, sl::VIEW::SIDE_BY_SIDE, sl::MEM::CPU);

            cv::Mat zedImageWrapped(zedImage.getHeight(), zedImage.getWidth(), CV_8UC4, zedImage.getPtr<sl::uchar4>(sl::MEM::CPU));


            cv::imshow("ZED Live", zedImageWrapped);

            if (cv::waitKey(1) == 27) break;
        }
    }

    // Close the camera
    zed.close();
    return EXIT_SUCCESS;
}
