object Excel_editor: TExcel_editor
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #1058#1072#1073#1083#1080#1095#1085#1099#1081' '#1088#1077#1076#1072#1082#1090#1086#1088
  ClientHeight = 568
  ClientWidth = 480
  Color = clBtnFace
  Constraints.MaxHeight = 607
  Constraints.MaxWidth = 496
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
    Top = 16
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
  object StringGrid1: TStringGrid
    Left = 8
    Top = 88
    Width = 465
    Height = 465
    ColCount = 3
    DefaultColWidth = 150
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Times New Roman'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goAlwaysShowEditor, goFixedRowDefAlign]
    ParentFont = False
    TabOrder = 1
    OnKeyPress = StringGrid1KeyPress
    OnSelectCell = StringGrid1SelectCell
  end
  object Button2: TButton
    Left = 264
    Top = 16
    Width = 209
    Height = 57
    Caption = #1057#1086#1093#1088#1072#1085#1080#1100' '#1092#1072#1081#1083
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button2Click
  end
  object OpenDialog1: TOpenDialog
    Left = 8
    Top = 88
  end
  object SaveDialog1: TSaveDialog
    Left = 32
    Top = 88
  end
end