#ifndef STARFIELD_H
#define STARFIELD_H

#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QTimer>
#include <QElapsedTimer>

class Starfield : public QOpenGLWidget
{
	Q_OBJECT

public:
	Starfield();
	~Starfield();

private:
	QOpenGLShader *vShader;
	QOpenGLShader *fShader;
	QOpenGLShaderProgram *program;
	QTimer *timer;
	QElapsedTimer *elapsedTimer;
	unsigned int vbo;
	unsigned int vao;

private slots:
	void onTimeout();

protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
};

#endif // STARFIELD_H
