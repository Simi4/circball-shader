#pragma once
#include <Qt3DRender/QGeometryRenderer>

namespace Qt3DRender {
    class QAttribute;
    class QBuffer;
}

class CircBallMesh : public Qt3DRender::QGeometryRenderer
{
    Q_OBJECT

public:
    explicit CircBallMesh(QNode *parent = nullptr);

private:
    Qt3DRender::QAttribute *m_positionAttribute;
    Qt3DRender::QAttribute *m_normalAttribute;
    Qt3DRender::QAttribute *m_colorAttribute;
    Qt3DRender::QAttribute *m_indexAttribute;

    Qt3DRender::QBuffer *m_vertexBuffer;
    Qt3DRender::QBuffer *m_indexBuffer;

    int m_resolution = 64;
    float m_radius = 1.0f;
};
