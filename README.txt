1) Cómo compilar y ejecutar la tarea:
- La tarea debe ser compilada desde un terminal bash utilizando el siguiente comando:
gcc -g main.c list.c -o main
- Se debe ejecutar con el siguiente comando desde un terminal bash:
./main.exe

2) Funcionamiento de opciones:
- Todas las funciones y opciones correspondientes al menú principal de la aplicación funcionan correctamente.
  El único error que se ha encontrado es al leer y escribir strings o archivos csv que contengan carácteres
  especiales del español como la letra ñ, este parece ser que es un problema de la interfaz de windows que
  por razones del idioma de configuración no admite como tal la lectura y escritura de los caracteres mencionados.
  Esto se intentó solucionar importado librerías que podrían solucionar esto como locale.h y windows.h pero no se
  obtuvieron resultados positivos.

3) Coevaluación:

4) Puntos de premio/castigo a cada integrante: