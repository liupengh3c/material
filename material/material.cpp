// material.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
int main()
{
    std::cout << "Hello World!\n" << std::endl;
    int width, height;
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "material study", nullptr, nullptr);
    if (!window)
    {
        std::cout << "failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH);
    // Shader,顶点着色器
    const GLchar* vertexShaderSource = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "layout (location = 1) in vec3 color;\n"
        "layout (location = 2) in vec3 aNormal;\n"

        "uniform mat4 model;\n"
        "uniform mat4 projection;\n"

        "out vec3 vertexColor;\n"
        "out vec3 Normal;\n"
        "out vec3 FragPos;\n"


        "void main()\n"
        "{\n"
        "gl_Position = projection * model * vec4(position, 1.0f);\n"
        "vertexColor = color;\n"
        "FragPos = vec3(model * vec4(position,1.0f));\n"
        "}\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
     
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    const GLchar* fragShaderSource =
        "#version 330 core\n"

        "in vec3 vertexColor;\n"
        "out vec4 color;\n"

        "struct Material\n"
        "{\n"
            "vec3 ambient;\n"
            "vec3 diffuse;\n"
            "vec3 specular;\n"
            "float shiniess;\n"
        "};\n"

        "uniform Material material;\n"
        "void main()\n"
        "{\n"
        "color = vec4(vertexColor,1.0f);\n"
        "}\n";

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    GLfloat vertices[] = {                      
                                                // 法向            
        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 0.0f,  1.0f,  0.0f,
    };

    // 设置顶点属性
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
        GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
        model = glm::rotate(model, 1.0f, glm::vec3(0.5f, 0.5f, 0.0f));
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
