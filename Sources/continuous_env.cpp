#include "continuous_env.h"

ContinuousEnvironment::ContinuousEnvironment(const int WIDTH, 
                                             const int HEIGHT, 
                                             QObject *parent)
{

}                                                  

void 
ContinuousEnvironment::ResetEnv(QGraphicsScene *scene)
{
    scene->clear();
}
