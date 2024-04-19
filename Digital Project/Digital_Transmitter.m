clc;clear ;close all;

instrhwinfo('Bluetooth','HC-05')
device = Bluetooth('HC-05', 1)
disp('Device is Connected ');


while(1)
    
    %% Transmitter
    mes=input('Enter the Message : ','s');
    [chrs,props]=find_msg_prop(mes);
    disp('Symbols Of The Message : ');
    disp(chrs);
    
    disp('Proppabilites Of Each Symbol : ');
    disp(props);
    
    [codebook] = binaryHuffman(props);
    disp('Code For Each Symbol : ');
    disp(codebook);
    mes_bin='';
    for i=1:length(mes)
        mes_bin=strcat(mes_bin,codebook(strfind(chrs,mes(i))));
    end
    
    disp('Message After Encoding In Binary : ');
    disp(mes_bin);
    
    %% Send Symbols To The Reciever
    
    fopen(device)
    for i=1:length(chrs)
        fwrite(device,chrs(i));
    end
    fclose(device)
    disp('Symbols Are Transmitted Successfully');
    
    fopen(device)
    for i=1:length(codebook)
        fwrite(device,char(codebook(i)));
        fwrite(device,',')
    end
    fclose(device)
    disp('Symbol Codes Are Transmitted Successfully');
    
    fopen(device)
    fwrite(device,char(mes_bin));
    fclose(device)
    disp('Binary Message Are Transmitted Successfully');
    
end





    