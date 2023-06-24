#include "Mesh.h"
#include "Renderer.h"
namespace roka
{
    roka::Mesh::Mesh()
        :Resource(enums::EResourceType::Mesh)
        ,mVertexBuffer(nullptr)
        ,mIndexBuffer(nullptr)
        , mVBDesc{}
        , mIBDesc{}
        ,mIndexCount(0)
    {
    }

    roka::Mesh::~Mesh()
    {
    }

    HRESULT roka::Mesh::Load(const std::wstring& path)
    {
        return E_NOTIMPL;
    }

    bool roka::Mesh::CreateVertexBuffer(void* data, UINT Count)
    {
        mVBDesc.ByteWidth = sizeof(renderer::Vertex) * Count;
        mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
        mVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
        mVBDesc.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA sub = {};
        sub.pSysMem = data;
        if (!graphics::GetDevice()->CreateBuffer(mVertexBuffer.GetAddressOf(), &mVBDesc, &sub))
        {
            return false;
        }
        return true;
    }

    bool roka::Mesh::CreateIndexBuffer(void* data, UINT Count)
    {
        mIndexCount = Count;
        mIBDesc.ByteWidth = sizeof(UINT) * Count;
        mIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
        mIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
        mIBDesc.CPUAccessFlags = 0;
        
        D3D11_SUBRESOURCE_DATA sub = {};
        sub.pSysMem = data;
        if (!graphics::GetDevice()->CreateBuffer(mIndexBuffer.GetAddressOf(), &mIBDesc, &sub))
        {
            return false;
        }
        return true;
    }

    void roka::Mesh::BindBuffer()
    {
        // input assembler ���������� ���� ����
        UINT stride = sizeof(renderer::Vertex);
        UINT offset = 0;
        graphics::GetDevice()->BindVertexBuffer(0, mVertexBuffer.GetAddressOf(), &stride, &offset);
        graphics::GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    }
    void Mesh::Render()
    {
        graphics::GetDevice()->DrawIndexed(mIndexCount, 0, 0);
    }
}

