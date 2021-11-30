#include <stdio.h>
#include <experimental/coroutine>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "implot.h"

#include "ECIMGUI.h"
#include "EvolveClimber.h"
#include "consts.h"

GLFWwindow* g_window;
ImGuiContext* imgui = 0;
ImPlotContext* implot = 0;
EC::EvolveClimber* evolveClimber = new EC::EvolveClimber();
EC::ECIMGUI* ecImgui = new EC::ECIMGUI(evolveClimber);

EM_JS(int, canvas_get_width, (), {
  return Module.canvas.width;
});

EM_JS(int, canvas_get_height, (), {
  return Module.canvas.height;
});

EM_JS(void, resizeCanvas, (), {
  js_resizeCanvas();
});

struct ReturnObject {
            struct promise_type {
                ReturnObject get_return_object() { return {}; }
                std::experimental::suspend_never initial_suspend() { return {}; }
                std::experimental::suspend_never final_suspend() noexcept { return {}; }
                void unhandled_exception() {}
                void return_void() noexcept {}
            };
        };

        struct Awaiter {
            std::experimental::coroutine_handle<> *hp_;
            constexpr bool await_ready() const noexcept { return false; }
            void await_suspend(std::experimental::coroutine_handle<> h) { *hp_ = h; }
            constexpr void await_resume() const noexcept {}
        };

        ReturnObject
            counter(std::experimental::coroutine_handle<> *continuation_out)
            {
                Awaiter a{continuation_out};
                for (unsigned i = 0;; ++i) {
                    co_await a;
                    std::cout << "counter: " << i << std::endl;
                }
            };

void loop()
{
  int width = canvas_get_width();
  int height = canvas_get_height();

  glfwSetWindowSize(g_window, width, height);

  ImGui::SetCurrentContext(imgui);
  ImPlot::SetCurrentContext(implot);

  glfwPollEvents();

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  if(ImGui::BeginMainMenuBar())
  {
    if(ImGui::MenuItem("Reset"))
    {
      delete evolveClimber;
      delete ecImgui;
      evolveClimber = new EC::EvolveClimber();
      ecImgui = new EC::ECIMGUI(evolveClimber);
    }

    if(ImGui::MenuItem("Settings"))
      ecImgui->onClickSettings();

    ImGui::SameLine(ImGui::GetWindowWidth()-335);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::EndMainMenuBar();
  }

  ecImgui->draw_main();

  ImGui::Render();

  ImVec4 clear_color = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
  int display_w, display_h;
  glfwMakeContextCurrent(g_window);
  glfwGetFramebufferSize(g_window, &display_w, &display_h);
  glViewport(0, -0, display_w, display_h);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  glfwMakeContextCurrent(g_window);
}

int init()
{
  if( !glfwInit() )
  {
      fprintf( stderr, "Failed to initialize GLFW\n" );
      return 1;
  }

  //glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

  // Open a window and create its OpenGL context
  int canvasWidth = 800;
  int canvasHeight = 600;
  g_window = glfwCreateWindow( canvasWidth, canvasHeight, "Evolve Climber", NULL, NULL);
  if( g_window == NULL )
  {
      fprintf( stderr, "Failed to open GLFW window.\n" );
      glfwTerminate();
      return -1;
  }
  glfwMakeContextCurrent(g_window); // Initialize GLEW

  // Create game objects
  // Setup Dear ImGui binding
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  ImPlot::CreateContext();

  ImGui_ImplGlfw_InitForOpenGL(g_window, false);
  ImGui_ImplOpenGL3_Init();

  // Setup style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  imgui = ImGui::GetCurrentContext();
  implot = ImPlot::GetCurrentContext();

  resizeCanvas();

  std::experimental::coroutine_handle<> h;
  counter(&h);
  for (int i = 0; i < 3; ++i) {
    std::cout << "In main1 function\n";
    h();
  }
  h.destroy();

  return 0;
}

void quit()
{
  delete evolveClimber;
  glfwTerminate();
}

extern "C" int main(int argc, char** argv)
{
  if (init() != 0) return 1;

  #ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
  #endif

  quit();

  return 0;
}
