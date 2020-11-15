#include "GEBase/EntryPoint.h"
#include "GEBase/Application.h"

int main(int argc, char **argv)
{ 
    Rocket::Application* app = Rocket::CreateApplication();
    app->Run();
    delete app;
    return 0;
}