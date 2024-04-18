clc;clear ;close all;
instrhwinfo('Bluetooth','HC-05')
% Create a bluetooth variable and open it at channel 1
device = Bluetooth('HC-05', 1)
% Pair with device
fopen(device)
disp('Device is Connected ')

while(1)
    %% Transmitter
    
    mes=input('Enter the Message : ','s');
    [chrs,props]=find_msg_prop(mes);
    [codebook] = binaryHuffman(props);
    codeRecieved=[];
    sym='';
    for i=1:length(mes)
        sym=append(sym,codebook(strfind(chrs,mes(i))));
    end
    sym

    %% Write command to HC-05/Arduino
    for i=1:length(chrs)
        fwrite(device,chrs(i));
        fwrite(device,',');
    end
 
    fwrite(device,'-');
    for i=1:length(codebook)
        fwrite(device,',');
        fwrite(device,char(codebook(i)));
    end
    fwrite(device,',-,');
    fwrite(device,char(sym));
    %% Reciever
    disp('Reciever Part')
    msgDecoded='';
    code='';
    sym=char(sym);
    l=length(sym);
    % sym=convertC  (sym)
    for i = 1:l
        code=strcat(code,sym(i));
        condArr=strcmp(codebook,code);
        flag=sum(condArr);
        if flag ==1
            for j = 1 : length(codebook)
                if condArr(j) == 1
                    msgDecoded = strcat(msgDecoded, chrs(j));
                    break;
                end
            end
            if i ~= l
            code='';
            end
        end
    end
end
    fclose(device)