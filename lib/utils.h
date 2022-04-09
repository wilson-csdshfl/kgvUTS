#include <fstream>

const char* const infoLogPath = "var/info.log";
const char* const errLogPath = "var/error.log";

inline std::string
getCurrDT()
{
  time_t now = time(NULL);
  struct tm tstruct;
  tstruct = *localtime(&now);
  char buff[21];
  strftime(buff, sizeof(buff), "%Y-%m-%d %X ", &tstruct);
  return std::string(buff);
}
static void
infoLog(const char* key, int err, const char* logBuff)
{
  std::ofstream logs(infoLogPath, std::ios_base::out | std::ios_base::app);
  logs << "\n" << getCurrDT() << key << err << " " << logBuff;
  logs.close();
}

static void
errLog(const char* key, int err, const char* logBuff)
{
  infoLog(key, err, logBuff);
  std::ofstream logs(errLogPath, std::ios_base::out | std::ios_base::app);
  logs << "\n" << getCurrDT() << key << err << " " << logBuff;
  logs.close();
}

static void
errCallback(int err, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
  errLog("Error: ", err, description);
  glfwTerminate();
}

static void
keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
      infoLog("Proc: ", 0, "ESCAPE key pressed");
    }
  else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
    {
      infoLog("Proc: ", 0, "ENTER key pressed");
    }
  else if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
    {
      infoLog("Proc: ", 0, "ADD key pressed");
    }
  else if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
    {
      infoLog("Proc: ", 0, "MINUS key pressed");
    }
  else
    {
      infoLog("Warn: ", 1, "not within keymap");
    }
}
