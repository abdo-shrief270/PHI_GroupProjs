clc;clear ;close all;
mes=input('Enter the Message : ','s');
[chrs,props]=find_msg_prop(mes);
[codebook] = binaryHuffman(props);
codeRecieved=[];
sym='';
for i=1:length(mes)
    sym=append(sym,codebook(strfind(chrs,mes(i))));
end
sym

instrhwinfo('Bluetooth','HC-05')
% Create a bluetooth variable and open it at channel 1
device = Bluetooth('HC-05', 1)
% Pair with device
fopen(device)
disp('Device is Connected ')
%% Write command to HC-05/Arduino
%fwrite(device, mes)
fwrite(device, convertCharsToStrings(sym))
fclose(device)