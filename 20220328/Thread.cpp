#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


// Pthread API Reference

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg); 

/* 
 ������ ������ ���ؼ� ����Ѵ�.
 1��° �ƱԸ�Ʈ�� thread�� �����尡 ���������� �����Ǿ����� ������ �����带 �ĺ��ϱ� ���ؼ� ���Ǵ� ������ �ĺ���
 2��° �ƱԸ�Ʈ�� attr�� ������ Ư���� �����ϱ� ���� ���, �⺻ ������ Ư���� �̿��ϰ��� �Ұ�쿡 NULL �� ���
 3��° �ƱԸ�Ʈ�� start_routine�� �б���Ѽ� ������ ������ �Լ�
 4��° �ƱԸմ��� arg�� ������ �Լ��� ����
 ���������� �����ɰ�� 0�� ����
 */

int pthread_join(pthread_t th, void **thread_return);

/* 
 1��° �ƱԸ�Ʈ th�� ��ٸ�(join)�� ������ �ĺ���
 2��° �ƱԸ�Ʈ thread_return�� �������� ����(return) ��
 thread_return �� NULL �� �ƴҰ�� �ش� �����ͷ� ������ ���� ���� �޾ƿü� �ִ�.
 */

 int pthread_detach(pthread_t th);

/* 
 main �����忡�� pthread_create �� �̿��� ������ �����带 �и�
 �ĺ���ȣ th�� �����带 detach �Ǿ������ �ش�(detach ��) �����尡 ����ɰ�� pthread_join �� ȣ������ �ʴ��� ��� ��� �ڿ��� ����(free) 
 */

 void pthread_exit(void *retval);

 /* 
  ���� �������� �����带 �����Ű���� �Ҷ� ���
  pthread_cleanup_push �� ���ǵǾ� �ִٸ�, pthread_exit �� ȣ��ɰ�� cleanup handler�� ȣ��
  ���� cleanup handler �� �޸𸮸� �����ϴ� ���� ���� �Ѵ�
  */

 void pthrad_cleanup_push(void(*routine) (void *), void *arg);

 /* 
  cleanup handlers �� �ν����ϱ� ���ؼ� ���
  pthread_exit(3)�� ȣ��Ǿ �����尡 ����ɶ� pthread_cleanup_push�� ���ؼ� �ν���� �Լ��� ȣ��
  routine�� �����尡 ����ɶ� ȣ��Ǵ� �Լ�, arg�� �ƱԸ�Ʈ
  cleanup handlers �� �ַ� �ڿ��� �ǵ����ְų�, mutex ��ݵ��� ������ ���� �뵵�� ���
  ���� mutex �������� pthread_exit �� ȣ��Ǿ� ������� �ٸ������忡�� ������ block �ɼ� �ֱ� ����
  malloc ���� �Ҵ���� �޸�, ���� ���������ڸ� �ݱ� ���ؼ��� ���
  */

 void pthread_cleanup_pop(int execute);

 /* 
  pthread_cleanup_push �� �Բ� ���
  install �� cleanup handler �� �����ϱ� ���ؼ� ���
  ���� execute �� 0 �̶��, pthread_cleanup_push �� ���� �ν���� cleanup handler �� (�����Ű�� �ʰ�)������ ��Ŵ
  0 �� �ƴ� ���ڶ�� cleanup handler �� �����Ű�� ����
  pthread_cleanup_push �� pthread_cleanup_pop �� �ݵ�� ���� �Լ����� ���� ������ ������ �ѽ����� ���
  */

 pthread_t pthread_self(void);

 /* pthread_self�� ȣ���ϴ� ���� �������� ������ĺ��ڸ� �ǵ����ش�.
  */


  // 2. ������ ����ȭ �Լ�

 int pthread_mutex_init(pthread_mutex_t * mutex, const pthread_mutex_attr *attr);

 /* 
  mutex �� �������� �����尡 �����ϴ� ����Ÿ�� ��ȣ�ϱ� ���ؼ� ���Ǵ� ����
  ��ȣ�ϰ��� �ϴ� ����Ÿ�� �ٷ�� �ڵ念���� ���� �ѹ��� �ϳ��� �����常 ���డ�� �ϵ��� �ϴ� ������� �����Ǵ� �����͸� ��ȣ
  �ڵ念��(�ϳ��� �����常 ����������)�� critical section �̶�� �ϸ�, mutex ���� API �� �̿��ؼ� ����
  pthread_mutex_init �� mutex ��ü�� �ʱ�ȭ ��Ű�� ���ؼ� ���
  1��° ���ڷ� �־����� mutex ��ü mutex�� �ʱ�ȭ
  2��° ������ attr �� �̿��ؼ� mutex Ư���� ����
  �⺻ mutex Ư���� �̿��ϱ� ���Ѵٸ� NULL �� ���
  mutex Ư��(����) ���� "fast", "recurisev", "error checking" �� ������ ������, �⺻���� "fast" �� ���
  */

 int pthread_mutex_destroy(pthread_mutex_t *mutex);

 /*
  ���ڷ� �־��� ���ؽ� ��ü mutex�� �����ϱ� ���ؼ� ���
  mutex �� pthread_mutex_init()�Լ��� �̿��ؼ� ������ ���ؽ� ��ü
  pthread_mutex_destroy �� �̿��ؼ� ����� mutex �� �����Ϸ��� �� mutex �� �ݵ�� unlock �����̾�� ��
  */

 int pthread_mutex_destroy(pthread_mutex_t *mutex);

 /*
  pthread_mutex_lock �� critcal section �� ���� ���ؼ� mutex lock �� ��û
  ���� �̹� �ٸ� �����忡�� mutex lock �� �� ����ϰ� �ִٸ� �ٸ� �����忡�� mutex lock(���ؽ� ���) �� �����Ҷ�����(����Ҽ� ����������) �� 
  ���� �ٸ� � �����忡���� mutex lock�� ����ϰ� ���� �ʴٸ�, ��� mutex lock �� ������ �ְ� �ǰ� critcal section�� �����ϰ� ��
  critcal section ������ ��� �۾��� ���ļ� ����ϰ� �ִ� mutex lock �� ���̻� �ʿ� ���ٸ� pthread_mutex_unlock �� ȣ���ؼ� mtuex lock �� �ǵ�����
  */

 int pthread_mutex_destroy(pthread_mutex_t *mutex);

 /*
  critical section ������ ��� �۾��� ��ġ�� mutex lock �� �����ֱ� ���ؼ� ���
  pthread_mutex_unlock �� �̿��ؼ� mutex lock �� �ǵ����ָ� �ٸ� �����忡�� mutex lock �� ������ �ִ� ���°� ��
  */

 int pthread_cond_init(pthread_cond_t *cond, const pthread_cond_attr *attr);

 /*
  pthread_cond_init�� ���ߺ��� (condition variable)cond�� �ʱ�ȭ�ϱ� ���ؼ� ���
  attr�� �̿��ؼ� ���Ǻ����� Ư���� �����Ҽ� ������, NULL�� �ٰ�� �⺻Ư������ �ʱ�ȭ
  ���Ǻ��� cond�� ��� PTHREAD_COND_INITIALIZER �� �̿��ؼ��� �ʱ�ȭ 
  */

 int pthread_cond_signal(pthread_cond_t *cond);

 /*
  ���Ǻ��� cond�� �ñ׳��� ����
  �ñ׳��� ������� cond���� ��ٸ���(wait) �����尡 �ִٸ� �����带 ����� �ȴ�(���Ⱑ Ǯ��)
  ���� ���Ǻ��� cond�� ��ٸ��� �����尡 ���ٸ�, �ƹ��� �ϵ� �Ͼ�� �ʰԵ�
  �������� �����尡 ��ٸ��� �ִٸ� ���� �ϳ��� �����忡�Ը� ����, �̶� � �����忡�� ��ȣ�� ���޵����� �˼� ���� 
  */

 int pthread_cond_broadcast(pthread_cond_t *cond);

 /*
  ���Ǻ��� cond���� ��ٸ���(wait) ��� �����忡�� ��ȣ�� ������, ����ٴ� ���� �����ϰ�� pthread_cond_signal�� �����ϰ� �۵�
  */

 int pthread_cond_wait(pthread_cond_t cond, pthread_mutex_t *mutex);

 /*
  ���Ǻ��� cond�� ���ؼ� ��ȣ�� ���޵ɶ����� ��
  ���� ��ȣ�� ���޵��� �ʴ´ٸ� ������ ���ɼ��� ����
  pthread_cond_wait�� ���Ǳ� ���� mutex ����� �ڵ����� �ǵ�����
  */

 int pthread_cond_timedwait(pthread_cont_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime);

 /*
  ���Ǻ��� cond�� ���ؼ� ��ȣ�� ���޵ɶ����� ���Ǹ� �ڵ����� mutex�� �����ִ� �������� pthread_cond_wait�� ����
  �׷��� �ð�üũ�� �����ؼ� abstime�ð����� ��ȣ�� �������� �ʴ´ٸ� error�� �߻��ϸ鼭 ����, �̶� ���ϰ��� ETIMEDOUT
  errno �� ���õǴ°� �ƴ�, ���ϰ����� ������ �Ѿ���°Ϳ� ����
  pthread_cond_timedwait�Լ��� �ٸ� signal �� ���ؼ� interrupted �ɼ� ������ �̶� EINTR �� ����
  �� �Լ��� ������ interrupted ��Ȳ�� ���� ó���� ���־�� ��
  */

 int pthread_cond_destroy(pthread_cond_t *cond);

 /*
  pthread_cond_init�� ���ؼ� ������ ���Ǻ���cond�� ���� �ڿ��� ����
  destroy �Լ��� ȣ���ϱ� ���� � �����嵵 cond������ �ñ׳��� ��ٸ��� �ʴ°� Ȯ��
  ���� cond �ñ׳��� ��ٸ��� �����尡 �����Ѵٸ� �� �Լ��� �����ϰ� EBUSY �� ����
  */


  // 3. Thread Attribute �Լ�

 int pthread_attr_init(pthread_attr_t *attr);

 /*
  pthread_attr_init�� thread attribute ��ü�� attr�� ����Ʈ ������ �ʱ�ȭ
  �����Ұ�� 0�� �����ְ� �����Ұ�� -1 �� �ǵ�����
  */

 int pthread_attr_destroy(pthread_attr_t *attr);

 /*
  pthread_attr_init�� ���� ������ thread attribute ��ü�� attr�� ����
  ���ŵ� attr �� �ٽ� ����ϱ� ���ؼ��� pthread_attr_init�� �̿��ؼ� �ٽ� �ʱ�ȭ �ؾ���
  */

 int pthread_attr_getscope(const pthread_attr_t *attr, int *scope);

 /*
  �����尡 � ����(scope)���� �ٷ������ �ִ����� ������ ���ؼ� ���
  PTHREAD_SCOPE_SYSTEM�� PTHREAD_SCOPE_PROCESS �� 2���� �����߿� ���� ����
  SYSTEM ���� ������� user ��� �������� �Ҹ�
  PROCESS ������� Ŀ�θ�� �������� �Ҹ�
  �������� ��� ������� �������ε�, �� Ŀ�ο��� �����带 �����층�ϴ� ����� �ƴ� ������ ���̺귯���� ���ؼ� �����带 �����층 �ϴ� ����� ���
  */

 int pthread_attr_setscope(pthread_attr_t *attr, int scope);

 /*
  �����尡 � ����(scope)���� �۵��ϰ� �Ұ����� �����ϱ� ���ؼ� ���
  �������� ��� Kernel mode �����带 �������� ����
  ���� PTHREAD_SCOPE_SYSTEM ���� ����
  �ݸ� �ֶ󸮽��� �������� Ŀ�θ���� ������ ����
  */

 int pthread_attr_getdetachstate(pthread_attr_t *attr, int detachstate);

 /*
  �����尡 join ������ ����(PTHREAD_CREATE_JOINABLE) ���� detached �������� (PTHREAD_CREATE_DETACHED) ������ �˾Ƴ�
  �˾Ƴ� ���� �ƱԸ�Ʈ detachstate�� ����
  �⺻�� PTHREAD_CREATE_JOINABLE �̸�, pthread_detach�� �̿��ؼ� ������ �����带 detach ���·� ���������� �Ǵ� pthread_attr_setdetachstate�Լ��� �̿��ؼ� �����带 detache ���·� ������������ PTHREAD_CREATE_DETACHED ���°� ��
  */

 int  pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);

 /*
  �������� ���¸� PTHREAD_CREATE_JOINABLE Ȥ�� PTHREAD_CREATE_DETACHED ���·� �����Ű�� ���ؼ� ���
  */


  // 4. ������ �ñ׳� ����

 int pthread_sigmask(int how, const sigset_t *newmask, sigset_t *oldmask);

 /*
  �����忡�� �ñ׳��� ���� ����
  �׷������� ���� ���μ����� �ñ׳��� ���޵Ǹ� ���μ����� ������ ��� ������� �ñ׳��� ����
  �׷��� Ư�� �����常 �ñ׳��� �޵��� �ϰ� ���� ���� ���� ��
  */

 int pthread_kill(pthread_t thread, int signo);

 /*
  ������ �ĺ���ȣ thread�� signo��ȣ�� �ñ׳��� �����Ѵ�.
  */

 int sigwait(const sigset_t *set, int *sig);

 /*
  �ñ׳� ������ ���������� ��ٸ�
  */


  // 5. ������ ���

 int pthread_cancel(pthread_t thread);

 int pthread_setcancelstate(int state, int *oldstate);

 int pthread_setcancelstate(int state, int *oldstate);

 int pthread_setcanceltype(int type, int *oldtype);

 void pthread_testcancel(void);