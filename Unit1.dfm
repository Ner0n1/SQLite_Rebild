object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 336
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 15
  object Label1: TLabel
    Left = 360
    Top = 179
    Width = 85
    Height = 15
    Caption = 'Addictional info'
  end
  object Label2: TLabel
    Left = 8
    Top = 11
    Width = 3
    Height = 15
  end
  object Memo1: TMemo
    Left = 360
    Top = 200
    Width = 185
    Height = 89
    Lines.Strings = (
      'Memo1')
    ReadOnly = True
    TabOrder = 0
  end
  object Button1: TButton
    Left = 360
    Top = 32
    Width = 153
    Height = 25
    Caption = 'Open BD and table'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 360
    Top = 81
    Width = 73
    Height = 25
    Caption = 'Delete'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 440
    Top = 81
    Width = 73
    Height = 25
    Caption = 'Clear all'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 360
    Top = 136
    Width = 153
    Height = 25
    Caption = 'Close BD and table'
    TabOrder = 4
    OnClick = Button4Click
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 8
    Top = 32
    Width = 329
    Height = 289
    Header.AutoSizeIndex = 0
    TabOrder = 5
    OnAddToSelection = VirtualStringTree1AddToSelection
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'ID'
      end
      item
        Position = 1
        Text = 'Host'
        Width = 250
      end>
  end
end
