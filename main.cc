#include "led-matrix.h"
#include "graphics.h"
#include "Background.hpp"
#include "Widget.hpp"
#include "Device.hpp"

#include "nlohmann/json.hpp"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
using json = nlohmann::json;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

void drawImage(Canvas* c, sf::Image i);
void readJson(std::string dir);
void loadFrames(std::vector<sf::Image>& v, std::string dir, int frames);
void setDefaults(RGBMatrix::Options& defaults);

int main(int argc, char** argv) {
    // Init
    std::cout << "Clock Started!" << std::endl;

    RGBMatrix::Options defaults;
    setDefaults(defaults); 

    // Background setup
    std::vector<sf::Image> vec;
    loadFrames(vec, "backgrounds/kurukuru",6);
    Background bg(vec);
    Canvas* canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);

    // Debug
    std::ifstream f("settings.json");
    json data = json::parse(f);
    // Device Setup
    Device d;
    // Time Widget Setup
    rgb_matrix::Color color(120, 20, 50);
    TimeClock t;
    t.InitializeWidgetFromJson(data,0);
    
    d.AddWidget(&t);
    // Draw Loop
    if (canvas == NULL)
        return 1;
    
    while (true) {
        if (interrupt_received){
            canvas->Fill(0, 0, 0);
            canvas->Clear();
            return 0;
        }
        
        d.Display(canvas);
        
        // Frame Reset
        usleep(1000000 / 15); // / x frames per second
        canvas->Clear();  
    }
    
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    // End
    canvas->Clear();
    delete canvas;
    return 0;
}

void drawImage(Canvas* c, sf::Image i) {
   for (uint x = 0; x < i.getSize().x; x++) {
            for (uint y = 0; y < i.getSize().y; y++) {
                sf::Color color = i.getPixel(x,y);
                c->SetPixel(x,y,color.r,color.g,color.b);
            }
        } 
}

void loadFrames(std::vector<sf::Image>& v, std::string dir, int frames){
    for (int i = 0; i < frames; i++) {
        sf::Image img;
        img.loadFromFile(dir + "/" + std::to_string(i) + ".png");
        v.push_back(img);
    }
}

void setDefaults(RGBMatrix::Options& defaults) {
    defaults.rows = 32;
    defaults.cols = 64;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.show_refresh_rate = false;
}

void readJson(std::string dir) {
    std::ifstream f("settings.json");
    json data = json::parse(f);
    std::cout << data["widget"]["id"] << std::endl;
}


