import QtQuick 2.9
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

Material {
    effect: Effect {
        techniques: [
            Technique {
                graphicsApiFilter {
                    api: GraphicsApiFilter.OpenGL
                    profile: GraphicsApiFilter.CoreProfile
                    majorVersion: 3
                    minorVersion: 3
                }

                filterKeys: [
                    FilterKey {
                        name: "renderingStyle"
                        value: "forward"
                    }
                ]

                parameters: [
                    Parameter {
                        name: "cameraPos"
                        value: cameraRoot.position
                    }
                ]

                renderPasses: [
                    RenderPass {
                        shaderProgram: ShaderProgram {
                            vertexShaderCode: loadSource("qrc:/shaders/overlay.vert")
                            fragmentShaderCode: loadSource("qrc:/shaders/overlay.frag")
                        }
                    }
                ]
            }
        ]
    }
}
