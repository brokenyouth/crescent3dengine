#include "RenderCommand.h"
#include "Logger.h"
#include <GL/glew.h>

RenderMesh::RenderMesh(Shader* Shader, Mesh* Mesh)
	: mShader(Shader), mMesh(Mesh)
{

}

void RenderMesh::Execute(glm::mat4 Model)
{
	mShader->Bind();

    const std::vector<Texture*> Textures = mMesh->GetTextures();

    mShader->SetUniformMat4("ModelMatrix", Model);

	uint32_t MeshVAO = mMesh->GetVAO();

    glBindVertexArray(MeshVAO);

    for (auto i = 0; i < Textures.size(); ++i)
    {
        Texture* InTexture = Textures[i];
        InTexture->BindTextureUnit(mShader, InTexture->GetType(), i);
    }

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glDrawElements(GL_TRIANGLES, mMesh->GetVertexCount(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

	mShader->Unbind();
}
