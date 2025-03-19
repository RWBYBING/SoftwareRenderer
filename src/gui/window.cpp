#include <gui/window.h>

#include <cstdio>
#include <iostream>

#include <core/renderer/renderer_factory.h>

using namespace GUI;

static const unsigned int SCREEN_WIDTH = 1400;
static const unsigned int SCREEN_HEIGHT = 1000;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void SetupImGuiStyle()
{
    // Moonlight style by Madam-Herta from ImThemes
    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.35f;
    style.WindowPadding = ImVec2(12.0f, 12.0f);
    style.WindowRounding = 11.5f;
    style.WindowBorderSize = 0.0f;
    style.WindowMinSize = ImVec2(20.0f, 20.0f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.ChildRounding = 0.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 0.0f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(20.0f, 3.400000095367432f);
    style.FrameRounding = 5.89999961853027f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(4.300000190734863f, 5.5f);
    style.ItemInnerSpacing = ImVec2(7.099999904632568f, 1.799999952316284f);
    style.CellPadding = ImVec2(12.10000038146973f, 9.199999809265137f);
    //style.IndentSpacing = 0.0f;
    style.ColumnsMinSpacing = 4.900000095367432f;
    style.ScrollbarSize = 11.60000038146973f;
    style.ScrollbarRounding = 15.89999961853027f;
    style.GrabMinSize = 3.700000047683716f;
    style.GrabRounding = 20.0f;
    style.TabRounding = 0.0f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.19411764889955521f, 0.2019607856869698f, 0.2176470592617989f, 1.0f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.6568627506494522f, 0.668627455830574f, 0.6921568661928177f, 1.0f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.3137254908680916f, 0.325490203499794f, 0.3529411822557449f, 1.0f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4568627506494522f, 0.468627455830574f, 0.4921568661928177f, 1.0f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.4568627506494522f, 0.468627455830574f, 0.4921568661928177f, 1.0f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.3568627506494522f, 0.368627455830574f, 0.3921568661928177f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.3176470592617989f, 0.3333333402872086f, 0.3490196138620377f, 1.0f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.9725490212440491f, 1.0f, 0.4980392158031464f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.9725490212440491f, 1.0f, 0.4980392158031464f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 0.7960784435272217f, 0.4980392158031464f, 1.0f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.4803921610116959f, 0.4882352977991104f, 0.496078434586525f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.4529411822557449f, 0.4529411822557449f, 0.4529411822557449f, 1.0f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.1411764770746231f, 0.1647058874368668f, 0.2078431397676468f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.305882354080677f, 0.305882354080677f, 0.305882354080677f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.3784313753247261f, 0.38627451211214066f, 0.4019607856869698f, 1.0f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.6694117718935013f, 0.6890196138620377f, 0.6321568661928177f, 1.0f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.6568627506494522f, 0.6843137294054031f, 0.650980406999588f, 1.0f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.6568627506494522f, 0.6843137294054031f, 0.650980406999588f, 1.0f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1450980454683304f, 1.0f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.9725490212440491f, 1.0f, 0.4980392158031464f, 1.0f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.4176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.125490203499794f, 0.2745098173618317f, 0.572549045085907f, 1.0f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.03921568766236305f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8823529481887817f, 0.7960784435272217f, 0.5607843399047852f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.95686274766922f, 0.95686274766922f, 0.95686274766922f, 1.0f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.9372549057006836f, 0.9372549057006836f, 0.9372549057006836f, 1.0f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2666666805744171f, 0.2901960909366608f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f); 
}

GLFWWindowManager::GLFWWindowManager()
    : renderer{nullptr}
    , render_mode{0}
{
    // Initialize GLFW Pipeline
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        glfwTerminate();
    }

    // GL 3.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    // Decide GLSL version
#ifdef __APPLE__
  // GLSL 150
    const char* glsl_version = "#version 150";
#else
  // GLSL 130
    const char* glsl_version = "#version 130";
#endif

    // Create window with graphics context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Renderer", NULL, NULL);
    if (window == nullptr)
    {
        glfwTerminate();
    }

    // glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    if (gl3wInit() != 0) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        glfwTerminate();
    }

    // Init ImGui Context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    static_cast<void>(io);
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // enable keyboard input
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // enable Docking
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // enable Multi-Viewport

    // Set Font Size
    float baseFontSize = 20.0f;
    ImFont* font = io.Fonts->AddFontFromFileTTF("/usr/share/fonts/google-noto/NotoSansMath-Regular.ttf", baseFontSize, nullptr,
        io.Fonts->GetGlyphRangesChineseFull());
    IM_ASSERT(font != nullptr);

    // Standarized the GLFW Window
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Set Window Style
    SetupImGuiStyle();

    // Init OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

GLFWWindowManager::~GLFWWindowManager()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void GLFWWindowManager::Run()
{
    this->Startup();

    // Main loop
#ifdef __EMSCRIPTEN__
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        glfwPollEvents();

        // ImGui render next frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        this->Update();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif
}

void GLFWWindowManager::Startup()
{
    // Init Backend Renderer
    Core::Renderer::SoftwareRendererFactory software_renderer_factory;
    this->renderer = software_renderer_factory.CreateRenderer();
    this->renderer->Init();
    this->renderer->SetupPipeline();
}

void GLFWWindowManager::Update()
{
    this->UpdateController();
    this->UpdateFramebuffer();
}

void GLFWWindowManager::UpdateController()
{
    if (ImGui::Begin("Controller"))
    {
        ImGui::Text("Frame Rate: %f", ImGui::GetIO().Framerate);

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Renderer: ");  ImGui::SameLine();
        ImGui::RadioButton("Software", &this->render_mode, 0);  ImGui::SameLine();
        ImGui::BeginDisabled();
        ImGui::RadioButton("OpenGL", &this->render_mode, 1);    ImGui::SameLine();
        ImGui::RadioButton("Vulkan", &this->render_mode, 2);
        ImGui::EndDisabled();

        ImGui::Text("Choose Objects: ");

        if (ImGui::CollapsingHeader("Vertex Processing"))
        {

        }

        if (ImGui::CollapsingHeader("Triangle Processing"))
        {

        }

        if (ImGui::CollapsingHeader("Rasterization"))
        {

        }

        if (ImGui::CollapsingHeader("Fragment Processing"))
        {

        }

        if (ImGui::CollapsingHeader("FrameBuffer Operation"))
        {

        }
    }
    ImGui::End();
}

void GLFWWindowManager::UpdateFramebuffer()
{
    if (ImGui::Begin("Result"))
    {
        ImVec2 window_size = ImGui::GetContentRegionAvail();
        // Resize the texture size when window size changed
        int current_width = static_cast<int>(window_size.x);
        int current_height = static_cast<int>(window_size.y);
        int texture_width = this->renderer->GetTextureWidth();
        int texture_height = this->renderer->GetTextureHeight();

        if (current_width != texture_width || current_height != texture_height)
        {
            this->renderer->HandleWindowResize(current_width, current_height);
            std::cout << "Window Resized: " << current_width << ", " << current_height << std::endl;
        }

        // render given texture
        GLuint texture = this->renderer->Render();
        ImGui::Image((void*)(intptr_t)texture, window_size);
    }
    ImGui::End();
}