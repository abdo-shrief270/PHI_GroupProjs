function varargout = source_coding(varargin)
% SOURCE_CODING MATLAB code for source_coding.fig
%      SOURCE_CODING, by itself, creates a new SOURCE_CODING or raises the existing
%      singleton*.
%
%      H = SOURCE_CODING returns the handle to a new SOURCE_CODING or the handle to
%      the existing singleton*.
%
%      SOURCE_CODING('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SOURCE_CODING.M with the given input arguments.
%
%      SOURCE_CODING('Property','Value',...) creates a new SOURCE_CODING or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before source_coding_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to source_coding_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help source_coding

% Last Modified by GUIDE v2.5 17-Apr-2024 08:15:50

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @source_coding_OpeningFcn, ...
                   'gui_OutputFcn',  @source_coding_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before source_coding is made visible.
function source_coding_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to source_coding (see VARARGIN)

% Choose default command line output for source_coding
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes source_coding wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = source_coding_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in clr_btn.
function clr_btn_Callback(hObject, eventdata, handles)
set(handles.s1,'string','');    
set(handles.s1_code,'string','');    

set(handles.s11,'string','');     
set(handles.s11_code,'string','');    

set(handles.s2,'string','');     
set(handles.s2_code,'string','');  

set(handles.s22,'string','');     
set(handles.s22_code,'string','');   

set(handles.s3,'string','');     
set(handles.s3_code,'string','');    

set(handles.s33,'string','');        
set(handles.s33_code,'string','');  

set(handles.s4,'string','');       
set(handles.s4_code,'string',''); 

set(handles.s44,'string','');    
set(handles.s44_code,'string',''); 

set(handles.s5,'string','');     
set(handles.s5_code,'string',''); 

set(handles.s55,'string','');    
set(handles.s55_code,'string',''); 

set(handles.s6,'string','');     
set(handles.s6_code,'string',''); 

set(handles.s66,'string','');     
set(handles.s66_code,'string',''); 

set(handles.s7,'string','');     
set(handles.s7_code,'string',''); 

set(handles.s77,'string','');    
set(handles.s77_code,'string',''); 

set(handles.s8,'string','');      
set(handles.s8_code,'string',''); 

set(handles.s88,'string','');      
set(handles.s88_code,'string',''); 

set(handles.s9,'string','');     
set(handles.s9_code,'string',''); 

set(handles.s99,'string','');     
set(handles.s99_code,'string',''); 

set(handles.s1010,'string','');      
set(handles.s1010_code,'string',''); 
set(handles.s1010,'string','');      
set(handles.s1010_code,'string',''); 


set(handles.lz_s1,'string','');  
set(handles.lz_code_s1,'string','');  

set(handles.lz_s2,'string',''); 
set(handles.lz_code_s2,'string','');  

set(handles.lz_s3,'string','');   
set(handles.lz_code_s3,'string','');  

set(handles.lz_s4,'string',''); 
set(handles.lz_code_s4,'string','');  

set(handles.lz_s5,'string',''); 
set(handles.lz_code_s5,'string','');  

set(handles.lz_s6,'string','');  
set(handles.lz_code_s6,'string','');

set(handles.lz_s7,'string',''); 
set(handles.lz_code_s7,'string',''); 

set(handles.lz_s8,'string',''); 
set(handles.lz_code_s8,'string','');  

set(handles.lz_s9,'string',''); 
set(handles.lz_code_s9,'string','');  

set(handles.lz_s10,'string',''); 
set(handles.lz_code_s10,'string','');  

set(handles.ent_huff,'string',''); 
set(handles.eff_huff,'string',''); 

set(handles.ent_shano,'string',''); 
set(handles.eff_shano,'string',''); 

set(handles.ent_lz,'string',''); 
set(handles.eff_lz,'string',''); 

set(handles.mes,'string','');


% --- Executes on button press in def_btn.
function def_btn_Callback(hObject, eventdata, handles)
mes_text='DDACCCAADDDACB';
set(handles.mes,'string',mes_text);  
sub_btn_Callback(hObject, eventdata, handles)


% --- Executes on button press in sub_btn.
function sub_btn_Callback(hObject, eventdata, handles)

%% todo source Coding
msg=get(handles.mes,'string');
[chars,chars_prop]=find_msg_prop(msg);
[code1, average_length] = binaryHuffman(chars_prop);
[code2, average_length2] = ShannonFano(chars_prop);
[codice, code_bin, code_book] = lempel_ziv(chars, msg);

if length(chars)<10
    for i=1:10-length(chars)
        chars(length(chars)+i)='-';
        code1(length(chars)+i)={'-'};
        code2(length(chars)+i)={'-'};
    end
end

length(code_bin);
code_bin(3,:);
if length(code_bin)<10
    for i=1:10-length(code_bin)
        code_bin(length(code_bin)+i,:)='---';
    end
end





set(handles.s1,'string',chars(1));    
set(handles.s1_code,'string',code1(1));    

set(handles.s11,'string',chars(1));     
set(handles.s11_code,'string',code2(1));    

set(handles.s2,'string',chars(2));     
set(handles.s2_code,'string',code1(2));  

set(handles.s22,'string',chars(2));     
set(handles.s22_code,'string',code2(2));   

set(handles.s3,'string',chars(3));     
set(handles.s3_code,'string',code1(3));    

set(handles.s33,'string',chars(3));        
set(handles.s33_code,'string',code2(3));  

set(handles.s4,'string',chars(4));       
set(handles.s4_code,'string',code1(4)); 

set(handles.s44,'string',chars(4));    
set(handles.s44_code,'string',code2(4)); 

set(handles.s5,'string',chars(5));     
set(handles.s5_code,'string',code1(5)); 

set(handles.s55,'string',chars(5));    
set(handles.s55_code,'string',code2(5)); 

set(handles.s6,'string',chars(6));     
set(handles.s6_code,'string',code1(6)); 

set(handles.s66,'string',chars(6));     
set(handles.s66_code,'string',code2(6)); 

set(handles.s7,'string',chars(7));     
set(handles.s7_code,'string',code1(7)); 

set(handles.s77,'string',chars(7));    
set(handles.s77_code,'string',code2(7)); 

set(handles.s8,'string',chars(8));      
set(handles.s8_code,'string',code1(8)); 

set(handles.s88,'string',chars(8));      
set(handles.s88_code,'string',code2(8)); 

set(handles.s9,'string',chars(9));     
set(handles.s9_code,'string',code1(9)); 

set(handles.s99,'string',chars(9));     
set(handles.s99_code,'string',code2(9)); 

set(handles.s10,'string',chars(10));      
set(handles.s10_code,'string',code1(10)); 

set(handles.s1010,'string',chars(10));      
set(handles.s1010_code,'string',code2(10)); 


set(handles.lz_s1,'string',code_book(1));  
set(handles.lz_code_s1,'string',code_bin(1,:));  

set(handles.lz_s2,'string',code_book(2)); 
set(handles.lz_code_s2,'string',code_bin(2,:));  

set(handles.lz_s3,'string',code_book(3));   
set(handles.lz_code_s3,'string',code_bin(3,:));  

set(handles.lz_s4,'string',code_book(4)); 
set(handles.lz_code_s4,'string',code_bin(4,:));  

set(handles.lz_s5,'string',code_book(5)); 
set(handles.lz_code_s5,'string',code_bin(5,:));  

set(handles.lz_s6,'string',code_book(6));  
set(handles.lz_code_s6,'string',code_bin(6,:));

set(handles.lz_s7,'string',code_book(7)); 
set(handles.lz_code_s7,'string',code_bin(7,:)); 

set(handles.lz_s8,'string',code_book(8)); 
set(handles.lz_code_s8,'string',code_bin(8,:));  

set(handles.lz_s9,'string',code_book(9)); 
set(handles.lz_code_s9,'string',code_bin(9,:));  

set(handles.lz_s10,'string',code_book(10)); 
set(handles.lz_code_s10,'string',code_bin(10,:));  

set(handles.ent_huff,'string',''); 
set(handles.eff_huff,'string',''); 

set(handles.ent_shano,'string',''); 
set(handles.eff_shano,'string',''); 

set(handles.ent_lz,'string',''); 
set(handles.eff_lz,'string',''); 



function mes_Callback(hObject, eventdata, handles)
% hObject    handle to mes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of mes as text
%        str2double(get(hObject,'String')) returns contents of mes as a double


% --- Executes during object creation, after setting all properties.
function mes_CreateFcn(hObject, eventdata, handles)
% hObject    handle to mes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
