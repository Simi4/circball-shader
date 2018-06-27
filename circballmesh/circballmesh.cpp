#include "circballmesh.h"
#include <Qt3DRender/qbuffer.h>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QGeometry>
#include <qmath.h>


QByteArray createCirclesVertexData(float radius, int resolution)
{
    QByteArray bufferBytes;

    // vec3 pos, vec3 normal, vec4 color
    const quint32 elementSize = 3 + 3 + 4;
    const quint32 stride = elementSize * sizeof(float);

    const int nVerts  = (resolution+1) * 3;

    bufferBytes.resize(stride * nVerts);

    float* fptr = reinterpret_cast<float*>(bufferBytes.data());

    const float dTheta = (M_PI * 2) / static_cast<float>( resolution );

    // 1
    for ( int lon = 0; lon < resolution+1; ++lon )
    {
        const float theta = static_cast<float>( lon ) * dTheta;
        const float cosTheta = qCos( theta );
        const float sinTheta = qSin( theta );

        *fptr++ = radius * cosTheta;
        *fptr++ = 0.0;
        *fptr++ = radius * sinTheta;

        *fptr++ = cosTheta;
        *fptr++ = 0.0; //
        *fptr++ = sinTheta;

        *fptr++ = 1.0f;
        *fptr++ = 0.0f;
        *fptr++ = 0.0f;
        *fptr++ = 1.0f;
    }

    // 2
    for ( int lon = 0; lon < resolution+1; ++lon )
    {
        const float theta = static_cast<float>( lon ) * dTheta;
        const float cosTheta = qCos( theta );
        const float sinTheta = qSin( theta );

        *fptr++ = radius * cosTheta;
        *fptr++ = radius * sinTheta;
        *fptr++ = 0.0;

        *fptr++ = cosTheta;
        *fptr++ = sinTheta;
        *fptr++ = 0.0;

        *fptr++ = 0.0f;
        *fptr++ = 1.0f;
        *fptr++ = 0.0f;
        *fptr++ = 1.0f;
    }

    // 3
    for ( int lon = 0; lon < resolution+1; ++lon )
    {
        const float theta = static_cast<float>( lon ) * dTheta;
        const float cosTheta = qCos( theta );
        const float sinTheta = qSin( theta );

        *fptr++ = 0.0;
        *fptr++ = radius * cosTheta;
        *fptr++ = radius * sinTheta;

        *fptr++ = 0.0;
        *fptr++ = cosTheta;
        *fptr++ = sinTheta;

        *fptr++ = 0.0f;
        *fptr++ = 0.0f;
        *fptr++ = 1.0f;
        *fptr++ = 1.0f;
    }

    return bufferBytes;
}

QByteArray createCirclesIndexData(int resolution)
{
    int linecnt = resolution * 2 * 3;

    QByteArray indexBytes;

    indexBytes.resize(linecnt * sizeof(quint16));
    quint16 *indexPtr = reinterpret_cast<quint16*>(indexBytes.data());

    int j = 0;
    for (int i = 0; i < resolution; ++i) {
        *indexPtr++ = j;
        *indexPtr++ = ++j;
    }

    j++;

    for (int i = 0; i < resolution; ++i) {
        *indexPtr++ = j;
        *indexPtr++ = ++j;
    }

    j++;

    for (int i = 0; i < resolution; ++i) {
        *indexPtr++ = j;
        *indexPtr++ = ++j;
    }

    return indexBytes;
}

CircBallMesh::CircBallMesh(QNode *parent) : QGeometryRenderer(parent)
{
    auto geometry = new Qt3DRender::QGeometry(this);

    setPrimitiveType(QGeometryRenderer::Lines);
    setGeometry(geometry);

    m_positionAttribute = new Qt3DRender::QAttribute(geometry);
    m_normalAttribute = new Qt3DRender::QAttribute(geometry);
    m_colorAttribute = new Qt3DRender::QAttribute(geometry);
    m_indexAttribute = new Qt3DRender::QAttribute(geometry);

    m_vertexBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, geometry);
    m_indexBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, geometry);

    m_vertexBuffer->setData(createCirclesVertexData(m_radius, m_resolution));
    m_indexBuffer->setData(createCirclesIndexData(m_resolution));

    const quint32 elementSize = 3 + 3 + 4;
    const quint32 stride = elementSize * sizeof(float);
    const int nVerts = (m_resolution+1) * 3;
    const int faces = m_resolution * 2 * 3;

    m_positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    m_positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    m_positionAttribute->setVertexSize(3);
    m_positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    m_positionAttribute->setBuffer(m_vertexBuffer);
    m_positionAttribute->setByteStride(stride);
    m_positionAttribute->setCount(nVerts);

    m_normalAttribute->setName(Qt3DRender::QAttribute::defaultNormalAttributeName());
    m_normalAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    m_normalAttribute->setVertexSize(3);
    m_normalAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    m_normalAttribute->setBuffer(m_vertexBuffer);
    m_normalAttribute->setByteStride(stride);
    m_normalAttribute->setByteOffset(3 * sizeof(float));
    m_normalAttribute->setCount(nVerts);

    m_colorAttribute->setName(Qt3DRender::QAttribute::defaultColorAttributeName());
    m_colorAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    m_colorAttribute->setVertexSize(4);
    m_colorAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    m_colorAttribute->setBuffer(m_vertexBuffer);
    m_colorAttribute->setByteStride(stride);
    m_colorAttribute->setByteOffset(6 * sizeof(float));
    m_colorAttribute->setCount(nVerts);

    m_indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    m_indexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedShort);
    m_indexAttribute->setBuffer(m_indexBuffer);
    m_indexAttribute->setCount(faces);

    geometry->addAttribute(m_positionAttribute);
    geometry->addAttribute(m_normalAttribute);
    geometry->addAttribute(m_colorAttribute);
    geometry->addAttribute(m_indexAttribute);
}
