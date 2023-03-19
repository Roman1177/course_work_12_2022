object Text_editor: TText_editor
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #1058#1077#1082#1089#1090#1086#1074#1099#1081' '#1088#1077#1076#1072#1082#1090#1086#1088
  ClientHeight = 568
  ClientWidth = 444
  Color = clBtnFace
  Constraints.MaxHeight = 607
  Constraints.MaxWidth = 460
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 8
    Top = 21
    Width = 209
    Height = 57
    Caption = #1053#1072#1079#1072#1076' '#1082' '#1075#1083#1072#1074#1085#1086#1081' '#1089#1090#1088#1072#1085#1080#1094#1077
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    WordWrap = True
    OnClick = Button1Click
  end
  object Button_save: TButton
    Left = 232
    Top = 21
    Width = 209
    Height = 57
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1092#1072#1081#1083
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    WordWrap = True
    OnClick = Button_saveClick
  end
  object Memo1: TMemo
    Left = 8
    Top = 96
    Width = 431
    Height = 465
    ScrollBars = ssBoth
    TabOrder = 2
    OnChange = Memo1Change
  end
  object OpenDialog1: TOpenDialog
    Left = 8
    Top = 80
  end
  object SaveDialog1: TSaveDialog
    Left = 32
    Top = 80
  end
end
