function [chars,chars_prop]=find_msg_prop(msg)
    msg_l=length(msg);
    chars='';
    k=1;

    for i=1:msg_l
        ch=msg(i);
        if sum(ismember(chars,ch)) ~=1
            chars=strcat(chars,msg(i));
        end
    end
    l=length(chars);
    chars_count=zeros(1,l);
    chars_prop=zeros(1,l);
    for i=1:l
        chars_count(i)=length(strfind(msg,chars(i)));
        chars_prop(i)=chars_count(i)/msg_l;
    end
end