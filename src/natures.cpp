
#include <Magnum/Magnum.h>

#define MAGNUM_TARGET_GLES3


#include <Corrade/Containers/Pointer.h>
#include <Corrade/Utility/StlMath.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/PixelFormat.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/Version.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/FunctionsBatch.h>
#include <Magnum/ImGuiIntegration/Context.hpp>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Primitives/Circle.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/Timeline.h>
#include <Magnum/Trade/MeshData.h>
#include <natures.hpp>


namespace Magnum {
    class Natures : public Platform::Application {
    public:
        explicit Natures(const Arguments &arguments);

    protected:
        void viewportEvent(ViewportEvent &event) override;

        void keyPressEvent(KeyEvent &event) override;

        void keyReleaseEvent(KeyEvent &event) override;

        void mousePressEvent(MouseEvent &event) override;

        void mouseReleaseEvent(MouseEvent &event) override;

        void mouseMoveEvent(MouseMoveEvent &event) override;

        void mouseScrollEvent(MouseScrollEvent &event) override;

        void textInputEvent(TextInputEvent &event) override;

        void drawEvent() override;

        /* Fluid simulation helper functions */
        void resetSimulation();


        /* Window control */
        void showMenu();

        bool _showMenu = true;
        ImGuiIntegration::Context _imGuiContext{NoCreate};
        bool _pausedSimulation = false;
        Timeline _timeline;
        Vector2 _lastMousePressedWorldPos;
        Float _mouseInteractionRadius = 5.0f;
        Float _mouseInteractionMagnitude = 5.0f;
        bool _bMouseInteraction = true;
        List L;

        Containers::Pointer<Scene2D> _scene;
        Containers::Pointer<SceneGraph::DrawableGroup2D> _drawableGroup;

        /* Camera helpers */
        Containers::Pointer<Object2D> _objCamera;
        Containers::Pointer<SceneGraph::Camera2D> _camera;

        /* Camera helpers */

//        SpriteBatch spriteBatch;
        SpriteBatch spriteBatch;
    };

}

namespace {
    constexpr Magnum::Int RadiusCircleBoundary = 45; /* radius of the boundary circle */
/* Viewport will display this window */
    const Magnum::Vector2i DomainDisplaySize = {WINDOW_Y, WINDOW_X};

    Magnum::Vector2 gridCenter() {
        return {WINDOW_Y / 2, WINDOW_X / 2};
    }

}

Magnum::Natures::Natures(const Arguments &arguments) : Platform::Application{arguments, NoCreate} {
    {
        const Vector2 dpiScaling = this->dpiScaling({});
        Configuration conf;
        conf.setTitle("Magnum 2D Fluid Simulation Example")
                .setSize(conf.size(), dpiScaling)
                .setWindowFlags(Configuration::WindowFlag::Resizable);
        GLConfiguration glConf;
        glConf.setSampleCount(dpiScaling.max() < 2.0f ? 8 : 2);
        if (!tryCreate(conf, glConf)) {
            create(conf, glConf.setSampleCount(0));
        }
    }
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImFontConfig fontConfig;
        fontConfig.FontDataOwnedByAtlas = false;
        const Vector2 size = Vector2{windowSize()} / dpiScaling();
        Utility::Resource rs{"data"};
        Containers::ArrayView<const char> font = rs.getRaw("SourceSansPro-Regular.ttf");
        ImGui::GetIO().Fonts->AddFontFromMemoryTTF(
                const_cast<char *>(font.data()), Int(font.size()),
                16.0f * framebufferSize().x() / size.x(), &fontConfig);

        _imGuiContext = ImGuiIntegration::Context{*ImGui::GetCurrentContext(),
                                                  Vector2{windowSize()} / dpiScaling(), windowSize(),
                                                  framebufferSize()};

        /* Setup proper blending to be used by ImGui */
        GL::Renderer::setBlendFunction(
                GL::Renderer::BlendFunction::SourceAlpha,
                GL::Renderer::BlendFunction::OneMinusSourceAlpha);
    }

    /* Setup scene objects and camera */
    {
        /* Setup scene objects */
        L = List();
        spriteBatch.init();


        _scene.emplace();
        _drawableGroup.emplace();

        /* Configure camera */
        _objCamera.emplace(_scene.get());
        _objCamera->setTransformation(Matrix3::translation(gridCenter()));

        _camera.emplace(*_objCamera);
        _camera->setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend)
                .setProjectionMatrix(Matrix3::projection(Vector2{DomainDisplaySize}))
                .setViewport(GL::defaultFramebuffer.viewport().size());
    }
    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::ProgramPointSize);

    /* Start the timer, loop at 60 Hz max */
    setSwapInterval(1);
    setMinimalLoopPeriod(16);
    _timeline.start();


#if !defined(MAGNUM_TARGET_WEBGL) && !defined(CORRADE_TARGET_ANDROID)
    /* Have some sane speed, please */
    setMinimalLoopPeriod(16);
#endif
}

void Magnum::Natures::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

    _imGuiContext.newFrame();

    /* Enable text input, if needed */
    /* Enable text input, if needed */
    if (ImGui::GetIO().WantTextInput && !isTextInputActive())
        startTextInput();
    else if (!ImGui::GetIO().WantTextInput && isTextInputActive())
        stopTextInput();


    L.Remove();;
    L.Behavior();
    L.Place();
    spriteBatch.begin();

    for (auto &organism : L.organisms)
        spriteBatch.draw(organism.getRectangle(), organism.getVisuals());

    spriteBatch.end();
//    spriteBatch.renderBatch();
    spriteBatch.drawShader(_camera, GL::defaultFramebuffer.viewport().size().y(), DomainDisplaySize.y());

    _camera->draw(*_drawableGroup);

    /* Menu for parameters */
    if (_showMenu) showMenu();

    /* Update application cursor */
    _imGuiContext.updateApplicationCursor(*this);

    /* Set appropriate states. If you only draw ImGui, it is sufficient to
       just enable blending and scissor test in the constructor. */
    GL::Renderer::enable(GL::Renderer::Feature::Blending);
    GL::Renderer::enable(GL::Renderer::Feature::ScissorTest);
    GL::Renderer::disable(GL::Renderer::Feature::FaceCulling);
    GL::Renderer::disable(GL::Renderer::Feature::DepthTest);

    _imGuiContext.drawFrame();

    /* Reset state. Only needed if you want to draw something else with
       different state after. */
    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);
    GL::Renderer::disable(GL::Renderer::Feature::ScissorTest);
    GL::Renderer::disable(GL::Renderer::Feature::Blending);
    swapBuffers();
    redraw();

}


void Magnum::Natures::viewportEvent(ViewportEvent &event) {
    GL::defaultFramebuffer.setViewport({{}, event.framebufferSize()});

    /* Relayout ImGui */
    _imGuiContext.relayout(Vector2{event.windowSize()} / event.dpiScaling(), event.windowSize(),
                           event.framebufferSize());

    /* Recompute the camera's projection matrix */
    _camera->setViewport(event.framebufferSize());
}

void Magnum::Natures::keyPressEvent(KeyEvent &event) {
//    switch (event.key()) {
//            case KeyEvent::Key::H:
//                _showMenu ^= true;
//                event.setAccepted(true);
//                break;
//            case KeyEvent::Key::R:
//                resetSimulation();
//                event.setAccepted(true);
//                break;
//            case KeyEvent::Key::Space:
//                _pausedSimulation ^= true;
//                event.setAccepted(true);
//                break;
//            default:
//                if (_imGuiContext.handleKeyPressEvent(event))
//                    event.setAccepted(true);
}

void Magnum::Natures::keyReleaseEvent(KeyEvent &event) {
    if (_imGuiContext.handleKeyReleaseEvent(event)) {
        event.setAccepted(true);
        return;
    }
}

void Magnum::Natures::mousePressEvent(MouseEvent &event) {
    if (_imGuiContext.handleMousePressEvent(event)) {
        event.setAccepted(true);
        return;
    }

}

void Magnum::Natures::mouseReleaseEvent(MouseEvent &event) {
    if (_imGuiContext.handleMouseReleaseEvent(event))
        event.setAccepted(true);

    if (_bMouseInteraction) {
//            _drawablePointer->setEnabled(false);
        event.setAccepted();
    }
}

void Magnum::Natures::mouseMoveEvent(MouseMoveEvent &event) {
    if (_imGuiContext.handleMouseMoveEvent(event)) {
        event.setAccepted(true);
        return;
    }

    if (!event.buttons()) return;

}

void Magnum::Natures::mouseScrollEvent(MouseScrollEvent &event) {
    const Float delta = event.offset().y();
    if (Math::abs(delta) < 1.0e-2f)
        return;

    if (_imGuiContext.handleMouseScrollEvent(event)) {
        /* Prevent scrolling the page */
        event.setAccepted();
        return;
    }
}

void Magnum::Natures::textInputEvent(TextInputEvent &event) {
    if (_imGuiContext.handleTextInputEvent(event))
        event.setAccepted(true);
}

void Magnum::Natures::showMenu() {
    ImGui::SetNextWindowPos({10.0f, 10.0f}, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowBgAlpha(0.5f);
    ImGui::Begin("Options", nullptr);

    /* General information */
    ImGui::Text("Hide/show menu: H");
//        ImGui::Text("Num. particles: %d", Int(_fluidSolver->numParticles()));
    ImGui::Text("Rendering: %3.2f FPS", Double(ImGui::GetIO().Framerate));
    ImGui::Spacing();

    /* Rendering parameters */
    if (ImGui::TreeNode("Particle Rendering")) {
        ImGui::PushID("Particle Rendering");
        {
            constexpr const char *items[] = {"Uniform", "Ramp by ID"};
            static Int colorMode = 1;
            ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
            if (ImGui::Combo("Color Mode", &colorMode, items, 2)) {
//                    _drawableParticles->setColorMode(ParticleSphereShader2D::ColorMode(colorMode));
            }
            ImGui::PopItemWidth();
            if (colorMode == 0) { /* Uniform color */
//                    static Color3 color = _drawableParticles->color();
//                    if (ImGui::ColorEdit3("Color", color.data())) {
//                        _drawableParticles->setColor(color);
//                    }
            }
        }
        ImGui::PopID();
        ImGui::TreePop();
    }
    ImGui::Spacing();
    ImGui::Separator();

    /* Simulation parameters */
    if (ImGui::TreeNodeEx("Simulation", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::PushID("Simulation");
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.3f);
//            ImGui::InputFloat("Speed", &_speed);
//            ImGui::Checkbox("Auto emit particles 5 times", &_bAutoEmitParticles);
        ImGui::PopItemWidth();
        ImGui::BeginGroup();
        ImGui::Checkbox("Mouse interaction", &_bMouseInteraction);
        if (_bMouseInteraction) {
            ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
            ImGui::SliderFloat("Radius", &_mouseInteractionRadius, 1.0f, 10.0f);
            ImGui::SliderFloat("Magnitude", &_mouseInteractionMagnitude, 1.0f, 10.0f);
            ImGui::PopItemWidth();
        }
        ImGui::EndGroup();
        ImGui::PopID();
        ImGui::TreePop();
    }
    ImGui::Spacing();
    ImGui::Separator();

    /* Reset */
    ImGui::Spacing();
    if (ImGui::Button("Emit Particles")) {
//            _fluidSolver->emitParticles();
    }
    ImGui::SameLine();
    if (ImGui::Button(_pausedSimulation ? "Play Sim" : "Pause Sim")) {
        _pausedSimulation ^= true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset Sim")) {
        resetSimulation();
    }
    ImGui::End();
}

void Magnum::Natures::resetSimulation() {
//        _fluidSolver->reset();
    _pausedSimulation = false;
//        _evolvedTime = 0.0f;
//        _numEmission = 0;
}


MAGNUM_APPLICATION_MAIN(Magnum::Natures)
