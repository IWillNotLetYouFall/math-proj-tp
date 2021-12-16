#include "RigidBody.h"
#include <iostream>

RigidBody::RigidBody(float masse)
{
	//this->shape.setScale(5, 5);
	SetScale(Vector3D(defaultsize, defaultsize, defaultsize));
	this->shape.setFillColor(Color::White);
	//this->shape.setOrigin(2.5f, 2.5f);
	setInertiaTensor(Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1));
	setMass(masse);
	setInertiaTensor(Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1));
}

RigidBody::RigidBody(Color color, float size)
{
	defaultsize = size;
	SetScale(Vector3D(size, size, size));
	this->shape.setFillColor(color);
	//this->shape.setOrigin(radius / 2, radius / 2);
	setInertiaTensor(Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1));
	setMass(1);
	setInertiaTensor(Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1));
}

void RigidBody::CalculateDerivedData()
{
	transformMatrix.setValue(0, 1 - 2 * orientation.getJ() * orientation.getJ() - 2 * orientation.getK() * orientation.getK());
	transformMatrix.setValue(1, 2 * orientation.getI() * orientation.getJ() - 2 * orientation.getW() * orientation.getK());
	transformMatrix.setValue(2, 2 * orientation.getI() * orientation.getK() + 2 * orientation.getW() * orientation.getJ());
	transformMatrix.setValue(3, position.x);
	transformMatrix.setValue(4, 2 * orientation.getI() * orientation.getJ() + 2 * orientation.getW() * orientation.getK());
	transformMatrix.setValue(5, 1 - 2 * orientation.getI() * orientation.getI() - 2 * orientation.getK() * orientation.getK());
	transformMatrix.setValue(6, 2 * orientation.getJ() * orientation.getK() - 2 * orientation.getW() * orientation.getI());
	transformMatrix.setValue(7, position.y);
	transformMatrix.setValue(8, 2 * orientation.getI() * orientation.getK() - 2 * orientation.getW() * orientation.getJ());
	transformMatrix.setValue(9, 2 * orientation.getJ() * orientation.getK() + 2 * orientation.getW() * orientation.getI());
	transformMatrix.setValue(10, 1 - 2 * orientation.getI() * orientation.getI() - 2 * orientation.getJ() * orientation.getJ());
	transformMatrix.setValue(11, position.z);

	float t4 = transformMatrix.values[0] * inverseInertiaTensor.values[0] +
		transformMatrix.values[1] * inverseInertiaTensor.values[3] +
		transformMatrix.values[2] * inverseInertiaTensor.values[6];
	float t9 = transformMatrix.values[0] * inverseInertiaTensor.values[1] +
		transformMatrix.values[1] * inverseInertiaTensor.values[4] +
		transformMatrix.values[2] * inverseInertiaTensor.values[7];
	float t14 = transformMatrix.values[0] * inverseInertiaTensor.values[2] +
		transformMatrix.values[1] * inverseInertiaTensor.values[5] +
		transformMatrix.values[2] * inverseInertiaTensor.values[8];
	float t28 = transformMatrix.values[4] * inverseInertiaTensor.values[0] +
		transformMatrix.values[5] * inverseInertiaTensor.values[3] +
		transformMatrix.values[6] * inverseInertiaTensor.values[6];
	float t33 = transformMatrix.values[4] * inverseInertiaTensor.values[1] +
		transformMatrix.values[5] * inverseInertiaTensor.values[4] +
		transformMatrix.values[6] * inverseInertiaTensor.values[7];
	float t38 = transformMatrix.values[4] * inverseInertiaTensor.values[2] +
		transformMatrix.values[5] * inverseInertiaTensor.values[5] +
		transformMatrix.values[6] * inverseInertiaTensor.values[8];
	float t52 = transformMatrix.values[8] * inverseInertiaTensor.values[0] +
		transformMatrix.values[9] * inverseInertiaTensor.values[3] +
		transformMatrix.values[10] * inverseInertiaTensor.values[6];
	float t57 = transformMatrix.values[8] * inverseInertiaTensor.values[1] +
		transformMatrix.values[9] * inverseInertiaTensor.values[4] +
		transformMatrix.values[10] * inverseInertiaTensor.values[7];
	float t62 = transformMatrix.values[8] * inverseInertiaTensor.values[2] +
		transformMatrix.values[9] * inverseInertiaTensor.values[5] +
		transformMatrix.values[10] * inverseInertiaTensor.values[8];
	inverseInertiaTensorWorld.values[0] = t4 * transformMatrix.values[0] +
		t9 * transformMatrix.values[1] +
		t14 * transformMatrix.values[2];
	inverseInertiaTensorWorld.values[1] = t4 * transformMatrix.values[4] +
		t9 * transformMatrix.values[5] +
		t14 * transformMatrix.values[6];
	inverseInertiaTensorWorld.values[2] = t4 * transformMatrix.values[8] +
		t9 * transformMatrix.values[9] +
		t14 * transformMatrix.values[10];
	inverseInertiaTensorWorld.values[3] = t28 * transformMatrix.values[0] +
		t33 * transformMatrix.values[1] +
		t38 * transformMatrix.values[2];
	inverseInertiaTensorWorld.values[4] = t28 * transformMatrix.values[4] +
		t33 * transformMatrix.values[5] +
		t38 * transformMatrix.values[6];
	inverseInertiaTensorWorld.values[5] = t28 * transformMatrix.values[8] +
		t33 * transformMatrix.values[9] +
		t38 * transformMatrix.values[10];
	inverseInertiaTensorWorld.values[6] = t52 * transformMatrix.values[0] +
		t57 * transformMatrix.values[1] +
		t62 * transformMatrix.values[2];
	inverseInertiaTensorWorld.values[7] = t52 * transformMatrix.values[4] +
		t57 * transformMatrix.values[5] +
		t62 * transformMatrix.values[6];
	inverseInertiaTensorWorld.values[8] = t52 * transformMatrix.values[8] +
		t57 * transformMatrix.values[9] +
		t62 * transformMatrix.values[10];
}

Vector3D RigidBody::getPointInWorldSpace(const Vector3D& point)
{
	Vector3D p = point;
	return orientation * p + position;
}

void RigidBody::Integrate(float duration)
{

	CalculateDerivedData();

	Vector3D m_FrameAcceleration = m_forceAccum * inverseMasse + lastFrameAcceleration;

	//Calcul Acc. angulaire
	auto angularAcceleration = inverseInertiaTensorWorld * m_torqueAccum;

	// / MAJ v�locit� lin�aire
	velocity += m_FrameAcceleration * duration;

	// MAJ v�locit� angulaire
	rotation += angularAcceleration * duration; 

	// Ajout du drag aux v�locit�s
	velocity *= powf(linearDamping, duration);
	rotation *= powf(m_angularDamping, duration);

	//MAJ position
	SetPosition(position + (velocity * duration));

	//MAJ rotation
	orientation.UpdateByAngularVelocity(rotation, duration);
	orientation.Normalized();

	Vector3D orienEuler = orientation.GetEulerAngles();
	shape.setRotation(orienEuler.x);

	std::cout << "Cube : " + position.ToString() << std::endl;

	CalculateDerivedData();

	lastFrameAcceleration = m_FrameAcceleration;

	//Simule la profondeur
	//� mettre en commentaire pour ne pas changer la grosseur de la boite
	float newsize = defaultsize / (1 + (position.z / 100));
	newsize = std::fmax(newsize, defaultsize / 4);
	newsize = std::fmin(newsize, defaultsize * 4);
	SetScale(Vector3D(newsize, newsize, newsize));

	ClearAccumulator();
}

void RigidBody::AddForce(const Vector3D& force)
{
	m_forceAccum += force;
}

void RigidBody::AddTorque(const Vector3D& torque)
{
	m_torqueAccum += torque;
}

void RigidBody::setInertiaTensor(const Matrix3& inertiaTensor)
{
	Matrix3 inverse = inertiaTensor;
	inverse = inverse.Inverse();
	inverseInertiaTensor = inverse;
}

void RigidBody::AddForceAtPoint(const Vector3D& force, const Vector3D& point)
{
	Vector3D pointLocal = (Vector3D)point - GetPosition();
	m_forceAccum += force;

	m_torqueAccum += pointLocal.VectorialProduct(force);
	//std::cout << "Force Accum : " + m_torqueAccum.ToString() << std::endl;
}

void RigidBody::AddForceAtBodyPoint(const Vector3D& force, const Vector3D& point)
{
	Vector3D worldP = getPointInWorldSpace(point);
	AddForceAtPoint(force, worldP);
}

void RigidBody::ClearAccumulator()
{
	m_forceAccum.x = 0;
	m_forceAccum.y = 0;
	m_forceAccum.z = 0;

	m_torqueAccum.x = 0;
	m_torqueAccum.y = 0;
	m_torqueAccum.z = 0;
}
