program pidigits;

var
  limit : integer;
  count : integer;
  q     : integer;
  r     : integer;
  t     : integer;
  k     : integer;
  n     : integer;
  l     : integer;

begin
  { Lee la cantidad de digitos deseada via linea de comando }
  limit := paramstr(1);
  count := 0;

  { Inicializa el estado del algoritmo de Gibbons }
  q := 1;
  r := 0;
  t := 1;
  k := 1;
  n := 3;
  l := 3;

  while count < limit do
    begin
      if 4 * q + r - t < n * t then
        begin
          { Si es el primer digito (count = 0), escribe el 3 y luego el punto }
          if count = 0 then
            begin
              write(n);
              write('.')
            end
          else
            write(n);

          count := count + 1;

          { grey box: Actualiza la matriz para extraer el proximo digito }
          r := 10 * (r - n * t);
          q := 10 * q;
          n := (3 * q + r) div t
        end
      else
        begin
          { Avanza a la serie matematica }
          r := (2 * q + r) * l;
          q := q * k;
          t := t * l;
          k := k + 1;
          l := l + 2;
          n := (3 * q + r) div t
        end
    end
end.