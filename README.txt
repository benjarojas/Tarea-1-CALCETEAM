1) Cómo compilar y ejecutar la tarea:
  - La tarea debe ser compilada desde un terminal bash utilizando el siguiente comando:
    gcc -g main.c list.c -o main
  - Se debe ejecutar con el siguiente comando desde un terminal bash:
    ./main.exe

2) Funcionamiento de opciones:
  - Todas las funciones y opciones correspondientes al menú principal de la aplicación funcionan correctamente.
    El único error que se ha encontrado es al leer y escribir strings o archivos csv que contengan carácteres
    especiales del español como la letra ñ, este parece ser que es un problema de la interfaz de windows que
    por razones de la configuración de idioma no admite como tal la lectura y escritura de los caracteres mencionados.
    Esto se intentó solucionar importado librerías como locale.h y windows.h pero no se obtuvieron resultados positivos.

3) Coevaluación:
  - Oscar Rojas:
  - Benjamin Rojas
  - Ramiro Magnatera:
  - Victor Granda: 

4) Puntos de premio/castigo a cada integrante:
- No incluimos puntos de premio/castigo ya que concluímos cada integrante trabajó bien y cumplió con las tareas acordadas entre todos.