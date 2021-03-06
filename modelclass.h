////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"
#include "inputclass.h"
#include "debug.h"
#include "component.h"
#include "colliderclass.h"
#include "meshclass.h"
#include "mymath.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////

// 각각의 오브젝트는 고유한 아이디를 가져야함
class ModelClass
{
protected:
	struct VertexType
	{
		Vector3f position;
		Vector2f texture;
		Vector3f normal;
	};

	int m_id;

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	D3DXMATRIX GetWorldMatrix();

	// 각각의 오브젝트 별로 따로 구현되는 함수들
	// 스크립트 부분을 여기서 짜도록 하면 될것!
	void SyncMatrix();

	virtual void Update();
	virtual void OnCollisionStay(ModelClass* model);
	virtual void Start();

	// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// 따로 수학 클래스를 만들어서 관리하면 좋을거 같음
	// D3DXVECTOR3만으로 하기에는 익숙하지 않은 부분이 많음
	const Vector3f& GetPosition() const{ return m_worldPosition; }
	const Vector3f& GetRotation() const{ return m_worldRotation; }
	const Vector3f& GetScale() const{ return m_worldScale; }
	
	void SetPosition(const Vector3f& position){ m_worldPosition = position; }
	void SetRotation(const Vector3f& rotation){ m_worldRotation = rotation; }
	void SetScale(const Vector3f& scale){ m_worldScale = scale; }

	// 오브젝트의 컴포넌트들을 관리하는 함수들
	const Component* GetComponent(COMPONENT_ID component_id) const;
	void SetComponent(COMPONENT_ID component_id, Component* component);
	void DeleteComponent(COMPONENT_ID component_id);
	bool isComponentExist(COMPONENT_ID component_id);

	// 자식 오브젝트를 관리하는 함수들
	void AddChild(ModelClass*);
	void DeleteChild(const int& k);
	ModelClass* GetChild(const int& i) const;
	vector<ModelClass*> GetChildren() const;

	void SetName(const string& str){ m_name = str; }
	const string& GetName(){ return m_name; }

	void Translate(const float& x, const float& y, const float& z);
	void Translate(const Vector3f& vec);

	void Rotate(const float& x, const float& y, const float& z);
	void Rotate(const Vector3f& vec);

	void Scaling(const float& x, const float& y, const float& z);
	void Scaling(const Vector3f& vec);

protected:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	virtual bool LoadModel();
	void ReleaseModel();

protected:

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;

	ModelType* m_model;
	int* m_model_indices;
	
	D3DXMATRIX m_worldMatrix;

	// 트리 구조 구현을 위한 부분
	// TODO!!!!!!!!!!!!!!!!!!!!!!!
	ModelClass* m_parent;
	vector<ModelClass*> m_children; 

	// GameObject class를 만들어 map으로
	// Component들을 넣음
	// 아직 사용 방식이 구리게 구현 됨
	map<COMPONENT_ID, Component*> m_components;

	// 이 행렬들을 조작하면 오브젝트의 움직임이 가능하도록 구현함
	Vector3f m_worldPosition;
	Vector3f m_worldScale;
	Vector3f m_worldRotation;

	// 속도
	// 이걸로 가속도 같은 것도 정할 수 있을 듯??
	Vector3f m_velocity;

	Mesh m_mesh;

	string m_name;
};

#endif