
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QPainter>
#include <QScreen>
#include <QWindow>


// class MainWindow : public QMainWindow {
//   Q_OBJECT
// public:
//   MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
//     QWidget *central = new QWidget(this);
//     setCentralWidget(central);

//     QVBoxLayout *layout = new QVBoxLayout(central);

//     QLabel *label = new QLabel("Hello Qt!", central);
//     QPushButton *button = new QPushButton("Click me", central);

//     layout->addWidget(label);
//     layout->addWidget(button);

//     connect(button, &QPushButton::clicked, this, [label]() { label->setText("Button clicked!"); });
//   }
// };

class OpenGLWindow : public QWindow, protected QOpenGLFunctions {
  Q_OBJECT
public:
  explicit OpenGLWindow(QWindow *parent = nullptr);
  ~OpenGLWindow();

  virtual void render(QPainter *painter);
  virtual void render();

  virtual void initialize();

  void setAnimating(bool animating);

public slots:
  void renderLater();
  void renderNow();

protected:
  bool event(QEvent *event) override;

  void exposeEvent(QExposeEvent *event) override;

private:
  bool m_animating = false;

  QOpenGLContext *m_context = nullptr;
  QOpenGLPaintDevice *m_device = nullptr;
};

class TriangleWindow : public OpenGLWindow {
public:
  using OpenGLWindow::OpenGLWindow;

  void initialize() override;
  void render() override;

private:
  GLint m_matrixUniform = 0;
  QOpenGLBuffer m_vbo;
  QOpenGLShaderProgram *m_program = nullptr;
  int m_frame = 0;
};