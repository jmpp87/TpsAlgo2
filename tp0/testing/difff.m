#!/usr/bin/octave -qf

%Calcula el error relativo de los datos esperados con los datos obtenidos
%Argumento 1 se especifica el nombre de archivo donde estan los complejos esperados (solo leer por linea)
%Argumento 2 se especifica el nombre de archivo donde estan los complejos obtenidos (solo leer por linea)
arg_list=argv();

esperado_str=arg_list{1};
obtenido_str=arg_list{2};

esperado_f = fopen(esperado_str,"r");
obtenido_f = fopen(obtenido_str,"r");

a = textscan(esperado_f,"%s", "delimiter",'\n');
b = textscan(obtenido_f,"%s", "delimiter",'\n');

a=char(a);
b=char(b);

for it=1:length(a(:,1))
	esperado = textscan(  a(it,:) ,"(%f,%f)");
	obtenido = textscan(  b(it,:) ,"(%f,%f)");
	esperado=cell2mat(esperado);
	obtenido=cell2mat(obtenido);
	
	z1 = esperado(:,1) .+ sqrt(-1) * esperado(:,2);
	z2 = obtenido(:,1) .+ sqrt(-1)* obtenido(:,2);

	num = sum( ( abs( z1 .- z2 ).^2 ) );
	den = sum( abs( z1 ).^2 );

	err = sqrt(num/den)
endfor	
