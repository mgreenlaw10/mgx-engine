#include "mgx/engine.hpp"

int main(int argc, char** argv) {
    mgx::Engine::GetInstance()->Init();
    mgx::Engine::GetInstance()->Start();
}
