package p2m

// NOTE: THIS FILE WAS PRODUCED BY THE
// MSGP CODE GENERATION TOOL (github.com/tinylib/msgp)
// DO NOT EDIT

import (
	"github.com/tinylib/msgp/msgp"
)

// DecodeMsg implements msgp.Decodable
func (z *FontInfo) DecodeMsg(dc *msgp.Reader) (err error) {
	var field []byte
	_ = field
	var zxvk uint32
	zxvk, err = dc.ReadMapHeader()
	if err != nil {
		return
	}
	for zxvk > 0 {
		zxvk--
		field, err = dc.ReadMapKeyPtr()
		if err != nil {
			return
		}
		switch msgp.UnsafeString(field) {
		case "Name":
			z.Name, err = dc.ReadString()
			if err != nil {
				return
			}
		case "Type":
			z.Type, err = dc.ReadString()
			if err != nil {
				return
			}
		case "Encoding":
			z.Encoding, err = dc.ReadString()
			if err != nil {
				return
			}
		case "Embedded":
			z.Embedded, err = dc.ReadBool()
			if err != nil {
				return
			}
		case "Subset":
			z.Subset, err = dc.ReadBool()
			if err != nil {
				return
			}
		case "ToUnicode":
			z.ToUnicode, err = dc.ReadBool()
			if err != nil {
				return
			}
		default:
			err = dc.Skip()
			if err != nil {
				return
			}
		}
	}
	return
}

// EncodeMsg implements msgp.Encodable
func (z *FontInfo) EncodeMsg(en *msgp.Writer) (err error) {
	// map header, size 6
	// write "Name"
	err = en.Append(0x86, 0xa4, 0x4e, 0x61, 0x6d, 0x65)
	if err != nil {
		return err
	}
	err = en.WriteString(z.Name)
	if err != nil {
		return
	}
	// write "Type"
	err = en.Append(0xa4, 0x54, 0x79, 0x70, 0x65)
	if err != nil {
		return err
	}
	err = en.WriteString(z.Type)
	if err != nil {
		return
	}
	// write "Encoding"
	err = en.Append(0xa8, 0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67)
	if err != nil {
		return err
	}
	err = en.WriteString(z.Encoding)
	if err != nil {
		return
	}
	// write "Embedded"
	err = en.Append(0xa8, 0x45, 0x6d, 0x62, 0x65, 0x64, 0x64, 0x65, 0x64)
	if err != nil {
		return err
	}
	err = en.WriteBool(z.Embedded)
	if err != nil {
		return
	}
	// write "Subset"
	err = en.Append(0xa6, 0x53, 0x75, 0x62, 0x73, 0x65, 0x74)
	if err != nil {
		return err
	}
	err = en.WriteBool(z.Subset)
	if err != nil {
		return
	}
	// write "ToUnicode"
	err = en.Append(0xa9, 0x54, 0x6f, 0x55, 0x6e, 0x69, 0x63, 0x6f, 0x64, 0x65)
	if err != nil {
		return err
	}
	err = en.WriteBool(z.ToUnicode)
	if err != nil {
		return
	}
	return
}

// MarshalMsg implements msgp.Marshaler
func (z *FontInfo) MarshalMsg(b []byte) (o []byte, err error) {
	o = msgp.Require(b, z.Msgsize())
	// map header, size 6
	// string "Name"
	o = append(o, 0x86, 0xa4, 0x4e, 0x61, 0x6d, 0x65)
	o = msgp.AppendString(o, z.Name)
	// string "Type"
	o = append(o, 0xa4, 0x54, 0x79, 0x70, 0x65)
	o = msgp.AppendString(o, z.Type)
	// string "Encoding"
	o = append(o, 0xa8, 0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67)
	o = msgp.AppendString(o, z.Encoding)
	// string "Embedded"
	o = append(o, 0xa8, 0x45, 0x6d, 0x62, 0x65, 0x64, 0x64, 0x65, 0x64)
	o = msgp.AppendBool(o, z.Embedded)
	// string "Subset"
	o = append(o, 0xa6, 0x53, 0x75, 0x62, 0x73, 0x65, 0x74)
	o = msgp.AppendBool(o, z.Subset)
	// string "ToUnicode"
	o = append(o, 0xa9, 0x54, 0x6f, 0x55, 0x6e, 0x69, 0x63, 0x6f, 0x64, 0x65)
	o = msgp.AppendBool(o, z.ToUnicode)
	return
}

// UnmarshalMsg implements msgp.Unmarshaler
func (z *FontInfo) UnmarshalMsg(bts []byte) (o []byte, err error) {
	var field []byte
	_ = field
	var zbzg uint32
	zbzg, bts, err = msgp.ReadMapHeaderBytes(bts)
	if err != nil {
		return
	}
	for zbzg > 0 {
		zbzg--
		field, bts, err = msgp.ReadMapKeyZC(bts)
		if err != nil {
			return
		}
		switch msgp.UnsafeString(field) {
		case "Name":
			z.Name, bts, err = msgp.ReadStringBytes(bts)
			if err != nil {
				return
			}
		case "Type":
			z.Type, bts, err = msgp.ReadStringBytes(bts)
			if err != nil {
				return
			}
		case "Encoding":
			z.Encoding, bts, err = msgp.ReadStringBytes(bts)
			if err != nil {
				return
			}
		case "Embedded":
			z.Embedded, bts, err = msgp.ReadBoolBytes(bts)
			if err != nil {
				return
			}
		case "Subset":
			z.Subset, bts, err = msgp.ReadBoolBytes(bts)
			if err != nil {
				return
			}
		case "ToUnicode":
			z.ToUnicode, bts, err = msgp.ReadBoolBytes(bts)
			if err != nil {
				return
			}
		default:
			bts, err = msgp.Skip(bts)
			if err != nil {
				return
			}
		}
	}
	o = bts
	return
}

// Msgsize returns the number of bytes occupied by the serialized message
func (z *FontInfo) Msgsize() (s int) {
	s = 1 + 5 + msgp.StringPrefixSize + len(z.Name) + 5 + msgp.StringPrefixSize + len(z.Type) + 9 + msgp.StringPrefixSize + len(z.Encoding) + 9 + msgp.BoolSize + 7 + msgp.BoolSize + 10 + msgp.BoolSize
	return
}

// DecodeMsg implements msgp.Decodable
func (z *FontInfos) DecodeMsg(dc *msgp.Reader) (err error) {
	var zajw uint32
	zajw, err = dc.ReadArrayHeader()
	if err != nil {
		return
	}
	if cap((*z)) >= int(zajw) {
		(*z) = (*z)[:zajw]
	} else {
		(*z) = make(FontInfos, zajw)
	}
	for zcmr := range *z {
		err = (*z)[zcmr].DecodeMsg(dc)
		if err != nil {
			return
		}
	}
	return
}

// EncodeMsg implements msgp.Encodable
func (z FontInfos) EncodeMsg(en *msgp.Writer) (err error) {
	err = en.WriteArrayHeader(uint32(len(z)))
	if err != nil {
		return
	}
	for zwht := range z {
		err = z[zwht].EncodeMsg(en)
		if err != nil {
			return
		}
	}
	return
}

// MarshalMsg implements msgp.Marshaler
func (z FontInfos) MarshalMsg(b []byte) (o []byte, err error) {
	o = msgp.Require(b, z.Msgsize())
	o = msgp.AppendArrayHeader(o, uint32(len(z)))
	for zwht := range z {
		o, err = z[zwht].MarshalMsg(o)
		if err != nil {
			return
		}
	}
	return
}

// UnmarshalMsg implements msgp.Unmarshaler
func (z *FontInfos) UnmarshalMsg(bts []byte) (o []byte, err error) {
	var zcua uint32
	zcua, bts, err = msgp.ReadArrayHeaderBytes(bts)
	if err != nil {
		return
	}
	if cap((*z)) >= int(zcua) {
		(*z) = (*z)[:zcua]
	} else {
		(*z) = make(FontInfos, zcua)
	}
	for zhct := range *z {
		bts, err = (*z)[zhct].UnmarshalMsg(bts)
		if err != nil {
			return
		}
	}
	o = bts
	return
}

// Msgsize returns the number of bytes occupied by the serialized message
func (z FontInfos) Msgsize() (s int) {
	s = msgp.ArrayHeaderSize
	for zxhx := range z {
		s += z[zxhx].Msgsize()
	}
	return
}

// DecodeMsg implements msgp.Decodable
func (z *Glyph) DecodeMsg(dc *msgp.Reader) (err error) {
	var zlqf uint32
	zlqf, err = dc.ReadArrayHeader()
	if err != nil {
		return
	}
	if zlqf != 2 {
		err = msgp.ArrayError{Wanted: 2, Got: zlqf}
		return
	}
	err = z.Rect.DecodeMsg(dc)
	if err != nil {
		return
	}
	z.Text, err = dc.ReadString()
	if err != nil {
		return
	}
	return
}

// EncodeMsg implements msgp.Encodable
func (z *Glyph) EncodeMsg(en *msgp.Writer) (err error) {
	// array header, size 2
	err = en.Append(0x92)
	if err != nil {
		return err
	}
	err = z.Rect.EncodeMsg(en)
	if err != nil {
		return
	}
	err = en.WriteString(z.Text)
	if err != nil {
		return
	}
	return
}

// MarshalMsg implements msgp.Marshaler
func (z *Glyph) MarshalMsg(b []byte) (o []byte, err error) {
	o = msgp.Require(b, z.Msgsize())
	// array header, size 2
	o = append(o, 0x92)
	o, err = z.Rect.MarshalMsg(o)
	if err != nil {
		return
	}
	o = msgp.AppendString(o, z.Text)
	return
}

// UnmarshalMsg implements msgp.Unmarshaler
func (z *Glyph) UnmarshalMsg(bts []byte) (o []byte, err error) {
	var zdaf uint32
	zdaf, bts, err = msgp.ReadArrayHeaderBytes(bts)
	if err != nil {
		return
	}
	if zdaf != 2 {
		err = msgp.ArrayError{Wanted: 2, Got: zdaf}
		return
	}
	bts, err = z.Rect.UnmarshalMsg(bts)
	if err != nil {
		return
	}
	z.Text, bts, err = msgp.ReadStringBytes(bts)
	if err != nil {
		return
	}
	o = bts
	return
}

// Msgsize returns the number of bytes occupied by the serialized message
func (z *Glyph) Msgsize() (s int) {
	s = 1 + z.Rect.Msgsize() + msgp.StringPrefixSize + len(z.Text)
	return
}

// DecodeMsg implements msgp.Decodable
func (z *Meta) DecodeMsg(dc *msgp.Reader) (err error) {
	var field []byte
	_ = field
	var zjfb uint32
	zjfb, err = dc.ReadMapHeader()
	if err != nil {
		return
	}
	for zjfb > 0 {
		zjfb--
		field, err = dc.ReadMapKeyPtr()
		if err != nil {
			return
		}
		switch msgp.UnsafeString(field) {
		case "Pages":
			z.Pages, err = dc.ReadInt64()
			if err != nil {
				return
			}
		case "FileName":
			z.FileName, err = dc.ReadString()
			if err != nil {
				return
			}
		case "Creator":
			z.Creator, err = dc.ReadString()
			if err != nil {
				return
			}
		case "Producer":
			z.Producer, err = dc.ReadString()
			if err != nil {
				return
			}
		case "FontInfo":
			if dc.IsNil() {
				err = dc.ReadNil()
				if err != nil {
					return
				}
				z.FontInfo = nil
			} else {
				if z.FontInfo == nil {
					z.FontInfo = new(FontInfos)
				}
				var zcxo uint32
				zcxo, err = dc.ReadArrayHeader()
				if err != nil {
					return
				}
				if cap(*z.FontInfo) >= int(zcxo) {
					*z.FontInfo = (*z.FontInfo)[:zcxo]
				} else {
					*z.FontInfo = make(FontInfos, zcxo)
				}
				for zpks := range *z.FontInfo {
					err = (*z.FontInfo)[zpks].DecodeMsg(dc)
					if err != nil {
						return
					}
				}
			}
		default:
			err = dc.Skip()
			if err != nil {
				return
			}
		}
	}
	return
}

// EncodeMsg implements msgp.Encodable
func (z *Meta) EncodeMsg(en *msgp.Writer) (err error) {
	// map header, size 5
	// write "Pages"
	err = en.Append(0x85, 0xa5, 0x50, 0x61, 0x67, 0x65, 0x73)
	if err != nil {
		return err
	}
	err = en.WriteInt64(z.Pages)
	if err != nil {
		return
	}
	// write "FileName"
	err = en.Append(0xa8, 0x46, 0x69, 0x6c, 0x65, 0x4e, 0x61, 0x6d, 0x65)
	if err != nil {
		return err
	}
	err = en.WriteString(z.FileName)
	if err != nil {
		return
	}
	// write "Creator"
	err = en.Append(0xa7, 0x43, 0x72, 0x65, 0x61, 0x74, 0x6f, 0x72)
	if err != nil {
		return err
	}
	err = en.WriteString(z.Creator)
	if err != nil {
		return
	}
	// write "Producer"
	err = en.Append(0xa8, 0x50, 0x72, 0x6f, 0x64, 0x75, 0x63, 0x65, 0x72)
	if err != nil {
		return err
	}
	err = en.WriteString(z.Producer)
	if err != nil {
		return
	}
	// write "FontInfo"
	err = en.Append(0xa8, 0x46, 0x6f, 0x6e, 0x74, 0x49, 0x6e, 0x66, 0x6f)
	if err != nil {
		return err
	}
	if z.FontInfo == nil {
		err = en.WriteNil()
		if err != nil {
			return
		}
	} else {
		err = en.WriteArrayHeader(uint32(len(*z.FontInfo)))
		if err != nil {
			return
		}
		for zpks := range *z.FontInfo {
			err = (*z.FontInfo)[zpks].EncodeMsg(en)
			if err != nil {
				return
			}
		}
	}
	return
}

// MarshalMsg implements msgp.Marshaler
func (z *Meta) MarshalMsg(b []byte) (o []byte, err error) {
	o = msgp.Require(b, z.Msgsize())
	// map header, size 5
	// string "Pages"
	o = append(o, 0x85, 0xa5, 0x50, 0x61, 0x67, 0x65, 0x73)
	o = msgp.AppendInt64(o, z.Pages)
	// string "FileName"
	o = append(o, 0xa8, 0x46, 0x69, 0x6c, 0x65, 0x4e, 0x61, 0x6d, 0x65)
	o = msgp.AppendString(o, z.FileName)
	// string "Creator"
	o = append(o, 0xa7, 0x43, 0x72, 0x65, 0x61, 0x74, 0x6f, 0x72)
	o = msgp.AppendString(o, z.Creator)
	// string "Producer"
	o = append(o, 0xa8, 0x50, 0x72, 0x6f, 0x64, 0x75, 0x63, 0x65, 0x72)
	o = msgp.AppendString(o, z.Producer)
	// string "FontInfo"
	o = append(o, 0xa8, 0x46, 0x6f, 0x6e, 0x74, 0x49, 0x6e, 0x66, 0x6f)
	if z.FontInfo == nil {
		o = msgp.AppendNil(o)
	} else {
		o = msgp.AppendArrayHeader(o, uint32(len(*z.FontInfo)))
		for zpks := range *z.FontInfo {
			o, err = (*z.FontInfo)[zpks].MarshalMsg(o)
			if err != nil {
				return
			}
		}
	}
	return
}

// UnmarshalMsg implements msgp.Unmarshaler
func (z *Meta) UnmarshalMsg(bts []byte) (o []byte, err error) {
	var field []byte
	_ = field
	var zeff uint32
	zeff, bts, err = msgp.ReadMapHeaderBytes(bts)
	if err != nil {
		return
	}
	for zeff > 0 {
		zeff--
		field, bts, err = msgp.ReadMapKeyZC(bts)
		if err != nil {
			return
		}
		switch msgp.UnsafeString(field) {
		case "Pages":
			z.Pages, bts, err = msgp.ReadInt64Bytes(bts)
			if err != nil {
				return
			}
		case "FileName":
			z.FileName, bts, err = msgp.ReadStringBytes(bts)
			if err != nil {
				return
			}
		case "Creator":
			z.Creator, bts, err = msgp.ReadStringBytes(bts)
			if err != nil {
				return
			}
		case "Producer":
			z.Producer, bts, err = msgp.ReadStringBytes(bts)
			if err != nil {
				return
			}
		case "FontInfo":
			if msgp.IsNil(bts) {
				bts, err = msgp.ReadNilBytes(bts)
				if err != nil {
					return
				}
				z.FontInfo = nil
			} else {
				if z.FontInfo == nil {
					z.FontInfo = new(FontInfos)
				}
				var zrsw uint32
				zrsw, bts, err = msgp.ReadArrayHeaderBytes(bts)
				if err != nil {
					return
				}
				if cap(*z.FontInfo) >= int(zrsw) {
					*z.FontInfo = (*z.FontInfo)[:zrsw]
				} else {
					*z.FontInfo = make(FontInfos, zrsw)
				}
				for zpks := range *z.FontInfo {
					bts, err = (*z.FontInfo)[zpks].UnmarshalMsg(bts)
					if err != nil {
						return
					}
				}
			}
		default:
			bts, err = msgp.Skip(bts)
			if err != nil {
				return
			}
		}
	}
	o = bts
	return
}

// Msgsize returns the number of bytes occupied by the serialized message
func (z *Meta) Msgsize() (s int) {
	s = 1 + 6 + msgp.Int64Size + 9 + msgp.StringPrefixSize + len(z.FileName) + 8 + msgp.StringPrefixSize + len(z.Creator) + 9 + msgp.StringPrefixSize + len(z.Producer) + 9
	if z.FontInfo == nil {
		s += msgp.NilSize
	} else {
		s += msgp.ArrayHeaderSize
		for zpks := range *z.FontInfo {
			s += (*z.FontInfo)[zpks].Msgsize()
		}
	}
	return
}

// DecodeMsg implements msgp.Decodable
func (z *Page) DecodeMsg(dc *msgp.Reader) (err error) {
	var field []byte
	_ = field
	var zobc uint32
	zobc, err = dc.ReadMapHeader()
	if err != nil {
		return
	}
	for zobc > 0 {
		zobc--
		field, err = dc.ReadMapKeyPtr()
		if err != nil {
			return
		}
		switch msgp.UnsafeString(field) {
		case "Number":
			z.Number, err = dc.ReadInt()
			if err != nil {
				return
			}
		case "Size":
			var zsnv uint32
			zsnv, err = dc.ReadArrayHeader()
			if err != nil {
				return
			}
			if zsnv != 2 {
				err = msgp.ArrayError{Wanted: 2, Got: zsnv}
				return
			}
			z.Size.W, err = dc.ReadFloat64()
			if err != nil {
				return
			}
			z.Size.H, err = dc.ReadFloat64()
			if err != nil {
				return
			}
		case "Glyphs":
			var zkgt uint32
			zkgt, err = dc.ReadArrayHeader()
			if err != nil {
				return
			}
			if cap(z.Glyphs) >= int(zkgt) {
				z.Glyphs = z.Glyphs[:zkgt]
			} else {
				z.Glyphs = make([]Glyph, zkgt)
			}
			for zxpk := range z.Glyphs {
				var zema uint32
				zema, err = dc.ReadArrayHeader()
				if err != nil {
					return
				}
				if zema != 2 {
					err = msgp.ArrayError{Wanted: 2, Got: zema}
					return
				}
				err = z.Glyphs[zxpk].Rect.DecodeMsg(dc)
				if err != nil {
					return
				}
				z.Glyphs[zxpk].Text, err = dc.ReadString()
				if err != nil {
					return
				}
			}
		case "Paths":
			var zpez uint32
			zpez, err = dc.ReadArrayHeader()
			if err != nil {
				return
			}
			if cap(z.Paths) >= int(zpez) {
				z.Paths = z.Paths[:zpez]
			} else {
				z.Paths = make([]Path, zpez)
			}
			for zdnj := range z.Paths {
				err = z.Paths[zdnj].DecodeMsg(dc)
				if err != nil {
					return
				}
			}
		default:
			err = dc.Skip()
			if err != nil {
				return
			}
		}
	}
	return
}

// EncodeMsg implements msgp.Encodable
func (z *Page) EncodeMsg(en *msgp.Writer) (err error) {
	// map header, size 4
	// write "Number"
	err = en.Append(0x84, 0xa6, 0x4e, 0x75, 0x6d, 0x62, 0x65, 0x72)
	if err != nil {
		return err
	}
	err = en.WriteInt(z.Number)
	if err != nil {
		return
	}
	// write "Size"
	// array header, size 2
	err = en.Append(0xa4, 0x53, 0x69, 0x7a, 0x65, 0x92)
	if err != nil {
		return err
	}
	err = en.WriteFloat64(z.Size.W)
	if err != nil {
		return
	}
	err = en.WriteFloat64(z.Size.H)
	if err != nil {
		return
	}
	// write "Glyphs"
	err = en.Append(0xa6, 0x47, 0x6c, 0x79, 0x70, 0x68, 0x73)
	if err != nil {
		return err
	}
	err = en.WriteArrayHeader(uint32(len(z.Glyphs)))
	if err != nil {
		return
	}
	for zxpk := range z.Glyphs {
		// array header, size 2
		err = en.Append(0x92)
		if err != nil {
			return err
		}
		err = z.Glyphs[zxpk].Rect.EncodeMsg(en)
		if err != nil {
			return
		}
		err = en.WriteString(z.Glyphs[zxpk].Text)
		if err != nil {
			return
		}
	}
	// write "Paths"
	err = en.Append(0xa5, 0x50, 0x61, 0x74, 0x68, 0x73)
	if err != nil {
		return err
	}
	err = en.WriteArrayHeader(uint32(len(z.Paths)))
	if err != nil {
		return
	}
	for zdnj := range z.Paths {
		err = z.Paths[zdnj].EncodeMsg(en)
		if err != nil {
			return
		}
	}
	return
}

// MarshalMsg implements msgp.Marshaler
func (z *Page) MarshalMsg(b []byte) (o []byte, err error) {
	o = msgp.Require(b, z.Msgsize())
	// map header, size 4
	// string "Number"
	o = append(o, 0x84, 0xa6, 0x4e, 0x75, 0x6d, 0x62, 0x65, 0x72)
	o = msgp.AppendInt(o, z.Number)
	// string "Size"
	// array header, size 2
	o = append(o, 0xa4, 0x53, 0x69, 0x7a, 0x65, 0x92)
	o = msgp.AppendFloat64(o, z.Size.W)
	o = msgp.AppendFloat64(o, z.Size.H)
	// string "Glyphs"
	o = append(o, 0xa6, 0x47, 0x6c, 0x79, 0x70, 0x68, 0x73)
	o = msgp.AppendArrayHeader(o, uint32(len(z.Glyphs)))
	for zxpk := range z.Glyphs {
		// array header, size 2
		o = append(o, 0x92)
		o, err = z.Glyphs[zxpk].Rect.MarshalMsg(o)
		if err != nil {
			return
		}
		o = msgp.AppendString(o, z.Glyphs[zxpk].Text)
	}
	// string "Paths"
	o = append(o, 0xa5, 0x50, 0x61, 0x74, 0x68, 0x73)
	o = msgp.AppendArrayHeader(o, uint32(len(z.Paths)))
	for zdnj := range z.Paths {
		o, err = z.Paths[zdnj].MarshalMsg(o)
		if err != nil {
			return
		}
	}
	return
}

// UnmarshalMsg implements msgp.Unmarshaler
func (z *Page) UnmarshalMsg(bts []byte) (o []byte, err error) {
	var field []byte
	_ = field
	var zqke uint32
	zqke, bts, err = msgp.ReadMapHeaderBytes(bts)
	if err != nil {
		return
	}
	for zqke > 0 {
		zqke--
		field, bts, err = msgp.ReadMapKeyZC(bts)
		if err != nil {
			return
		}
		switch msgp.UnsafeString(field) {
		case "Number":
			z.Number, bts, err = msgp.ReadIntBytes(bts)
			if err != nil {
				return
			}
		case "Size":
			var zqyh uint32
			zqyh, bts, err = msgp.ReadArrayHeaderBytes(bts)
			if err != nil {
				return
			}
			if zqyh != 2 {
				err = msgp.ArrayError{Wanted: 2, Got: zqyh}
				return
			}
			z.Size.W, bts, err = msgp.ReadFloat64Bytes(bts)
			if err != nil {
				return
			}
			z.Size.H, bts, err = msgp.ReadFloat64Bytes(bts)
			if err != nil {
				return
			}
		case "Glyphs":
			var zyzr uint32
			zyzr, bts, err = msgp.ReadArrayHeaderBytes(bts)
			if err != nil {
				return
			}
			if cap(z.Glyphs) >= int(zyzr) {
				z.Glyphs = z.Glyphs[:zyzr]
			} else {
				z.Glyphs = make([]Glyph, zyzr)
			}
			for zxpk := range z.Glyphs {
				var zywj uint32
				zywj, bts, err = msgp.ReadArrayHeaderBytes(bts)
				if err != nil {
					return
				}
				if zywj != 2 {
					err = msgp.ArrayError{Wanted: 2, Got: zywj}
					return
				}
				bts, err = z.Glyphs[zxpk].Rect.UnmarshalMsg(bts)
				if err != nil {
					return
				}
				z.Glyphs[zxpk].Text, bts, err = msgp.ReadStringBytes(bts)
				if err != nil {
					return
				}
			}
		case "Paths":
			var zjpj uint32
			zjpj, bts, err = msgp.ReadArrayHeaderBytes(bts)
			if err != nil {
				return
			}
			if cap(z.Paths) >= int(zjpj) {
				z.Paths = z.Paths[:zjpj]
			} else {
				z.Paths = make([]Path, zjpj)
			}
			for zdnj := range z.Paths {
				bts, err = z.Paths[zdnj].UnmarshalMsg(bts)
				if err != nil {
					return
				}
			}
		default:
			bts, err = msgp.Skip(bts)
			if err != nil {
				return
			}
		}
	}
	o = bts
	return
}

// Msgsize returns the number of bytes occupied by the serialized message
func (z *Page) Msgsize() (s int) {
	s = 1 + 7 + msgp.IntSize + 5 + 1 + msgp.Float64Size + msgp.Float64Size + 7 + msgp.ArrayHeaderSize
	for zxpk := range z.Glyphs {
		s += 1 + z.Glyphs[zxpk].Rect.Msgsize() + msgp.StringPrefixSize + len(z.Glyphs[zxpk].Text)
	}
	s += 6 + msgp.ArrayHeaderSize
	for zdnj := range z.Paths {
		s += z.Paths[zdnj].Msgsize()
	}
	return
}

// EncodeMsg implements msgp.Encodable
func (z *Path) EncodeMsg(en *msgp.Writer) (err error) {
	// map header, size 4
	// write "Type"
	err = en.Append(0x84, 0xa4, 0x54, 0x79, 0x70, 0x65)
	if err != nil {
		return err
	}
	err = en.WriteUint8(uint8(z.Type))
	if err != nil {
		return
	}
	// write "Data"
	err = en.Append(0xa4, 0x44, 0x61, 0x74, 0x61)
	if err != nil {
		return err
	}
	err = en.WriteArrayHeader(uint32(len(z.Data)))
	if err != nil {
		return
	}
	for zzpf := range z.Data {
		err = en.WriteArrayHeader(uint32(len(z.Data[zzpf])))
		if err != nil {
			return
		}
		for zrfe := range z.Data[zzpf] {
			err = en.WriteFloat64(z.Data[zzpf][zrfe])
			if err != nil {
				return
			}
		}
	}
	// write "StrokeWidth"
	err = en.Append(0xab, 0x53, 0x74, 0x72, 0x6f, 0x6b, 0x65, 0x57, 0x69, 0x64, 0x74, 0x68)
	if err != nil {
		return err
	}
	err = en.WriteFloat64(z.StrokeWidth)
	if err != nil {
		return
	}
	// write "Color"
	// map header, size 3
	// write "R"
	err = en.Append(0xa5, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x83, 0xa1, 0x52)
	if err != nil {
		return err
	}
	err = en.WriteUint8(z.Color.R)
	if err != nil {
		return
	}
	// write "G"
	err = en.Append(0xa1, 0x47)
	if err != nil {
		return err
	}
	err = en.WriteUint8(z.Color.G)
	if err != nil {
		return
	}
	// write "B"
	err = en.Append(0xa1, 0x42)
	if err != nil {
		return err
	}
	err = en.WriteUint8(z.Color.B)
	if err != nil {
		return
	}
	return
}

// MarshalMsg implements msgp.Marshaler
func (z *Path) MarshalMsg(b []byte) (o []byte, err error) {
	o = msgp.Require(b, z.Msgsize())
	// map header, size 4
	// string "Type"
	o = append(o, 0x84, 0xa4, 0x54, 0x79, 0x70, 0x65)
	o = msgp.AppendUint8(o, uint8(z.Type))
	// string "Data"
	o = append(o, 0xa4, 0x44, 0x61, 0x74, 0x61)
	o = msgp.AppendArrayHeader(o, uint32(len(z.Data)))
	for zzpf := range z.Data {
		o = msgp.AppendArrayHeader(o, uint32(len(z.Data[zzpf])))
		for zrfe := range z.Data[zzpf] {
			o = msgp.AppendFloat64(o, z.Data[zzpf][zrfe])
		}
	}
	// string "StrokeWidth"
	o = append(o, 0xab, 0x53, 0x74, 0x72, 0x6f, 0x6b, 0x65, 0x57, 0x69, 0x64, 0x74, 0x68)
	o = msgp.AppendFloat64(o, z.StrokeWidth)
	// string "Color"
	// map header, size 3
	// string "R"
	o = append(o, 0xa5, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x83, 0xa1, 0x52)
	o = msgp.AppendUint8(o, z.Color.R)
	// string "G"
	o = append(o, 0xa1, 0x47)
	o = msgp.AppendUint8(o, z.Color.G)
	// string "B"
	o = append(o, 0xa1, 0x42)
	o = msgp.AppendUint8(o, z.Color.B)
	return
}

// UnmarshalMsg implements msgp.Unmarshaler
func (z *Path) UnmarshalMsg(bts []byte) (o []byte, err error) {
	var field []byte
	_ = field
	var zgmo uint32
	zgmo, bts, err = msgp.ReadMapHeaderBytes(bts)
	if err != nil {
		return
	}
	for zgmo > 0 {
		zgmo--
		field, bts, err = msgp.ReadMapKeyZC(bts)
		if err != nil {
			return
		}
		switch msgp.UnsafeString(field) {
		case "Type":
			{
				var ztaf uint8
				ztaf, bts, err = msgp.ReadUint8Bytes(bts)
				z.Type = PathType(ztaf)
			}
			if err != nil {
				return
			}
		case "Data":
			var zeth uint32
			zeth, bts, err = msgp.ReadArrayHeaderBytes(bts)
			if err != nil {
				return
			}
			if cap(z.Data) >= int(zeth) {
				z.Data = z.Data[:zeth]
			} else {
				z.Data = make([][]float64, zeth)
			}
			for zzpf := range z.Data {
				var zsbz uint32
				zsbz, bts, err = msgp.ReadArrayHeaderBytes(bts)
				if err != nil {
					return
				}
				if cap(z.Data[zzpf]) >= int(zsbz) {
					z.Data[zzpf] = z.Data[zzpf][:zsbz]
				} else {
					z.Data[zzpf] = make([]float64, zsbz)
				}
				for zrfe := range z.Data[zzpf] {
					z.Data[zzpf][zrfe], bts, err = msgp.ReadFloat64Bytes(bts)
					if err != nil {
						return
					}
				}
			}
		case "StrokeWidth":
			z.StrokeWidth, bts, err = msgp.ReadFloat64Bytes(bts)
			if err != nil {
				return
			}
		case "Color":
			var zrjx uint32
			zrjx, bts, err = msgp.ReadMapHeaderBytes(bts)
			if err != nil {
				return
			}
			for zrjx > 0 {
				zrjx--
				field, bts, err = msgp.ReadMapKeyZC(bts)
				if err != nil {
					return
				}
				switch msgp.UnsafeString(field) {
				case "R":
					z.Color.R, bts, err = msgp.ReadUint8Bytes(bts)
					if err != nil {
						return
					}
				case "G":
					z.Color.G, bts, err = msgp.ReadUint8Bytes(bts)
					if err != nil {
						return
					}
				case "B":
					z.Color.B, bts, err = msgp.ReadUint8Bytes(bts)
					if err != nil {
						return
					}
				default:
					bts, err = msgp.Skip(bts)
					if err != nil {
						return
					}
				}
			}
		default:
			bts, err = msgp.Skip(bts)
			if err != nil {
				return
			}
		}
	}
	o = bts
	return
}

// Msgsize returns the number of bytes occupied by the serialized message
func (z *Path) Msgsize() (s int) {
	s = 1 + 5 + msgp.Uint8Size + 5 + msgp.ArrayHeaderSize
	for zzpf := range z.Data {
		s += msgp.ArrayHeaderSize + (len(z.Data[zzpf]) * (msgp.Float64Size))
	}
	s += 12 + msgp.Float64Size + 6 + 1 + 2 + msgp.Uint8Size + 2 + msgp.Uint8Size + 2 + msgp.Uint8Size
	return
}

// DecodeMsg implements msgp.Decodable
func (z *PathType) DecodeMsg(dc *msgp.Reader) (err error) {
	{
		var zawn uint8
		zawn, err = dc.ReadUint8()
		(*z) = PathType(zawn)
	}
	if err != nil {
		return
	}
	return
}

// EncodeMsg implements msgp.Encodable
func (z PathType) EncodeMsg(en *msgp.Writer) (err error) {
	err = en.WriteUint8(uint8(z))
	if err != nil {
		return
	}
	return
}

// MarshalMsg implements msgp.Marshaler
func (z PathType) MarshalMsg(b []byte) (o []byte, err error) {
	o = msgp.Require(b, z.Msgsize())
	o = msgp.AppendUint8(o, uint8(z))
	return
}

// UnmarshalMsg implements msgp.Unmarshaler
func (z *PathType) UnmarshalMsg(bts []byte) (o []byte, err error) {
	{
		var zwel uint8
		zwel, bts, err = msgp.ReadUint8Bytes(bts)
		(*z) = PathType(zwel)
	}
	if err != nil {
		return
	}
	o = bts
	return
}

// Msgsize returns the number of bytes occupied by the serialized message
func (z PathType) Msgsize() (s int) {
	s = msgp.Uint8Size
	return
}

// DecodeMsg implements msgp.Decodable
func (z *Rect) DecodeMsg(dc *msgp.Reader) (err error) {
	var zrbe uint32
	zrbe, err = dc.ReadArrayHeader()
	if err != nil {
		return
	}
	if zrbe != 4 {
		err = msgp.ArrayError{Wanted: 4, Got: zrbe}
		return
	}
	z.X1, err = dc.ReadFloat64()
	if err != nil {
		return
	}
	z.Y1, err = dc.ReadFloat64()
	if err != nil {
		return
	}
	z.X2, err = dc.ReadFloat64()
	if err != nil {
		return
	}
	z.Y2, err = dc.ReadFloat64()
	if err != nil {
		return
	}
	return
}

// EncodeMsg implements msgp.Encodable
func (z *Rect) EncodeMsg(en *msgp.Writer) (err error) {
	// array header, size 4
	err = en.Append(0x94)
	if err != nil {
		return err
	}
	err = en.WriteFloat64(z.X1)
	if err != nil {
		return
	}
	err = en.WriteFloat64(z.Y1)
	if err != nil {
		return
	}
	err = en.WriteFloat64(z.X2)
	if err != nil {
		return
	}
	err = en.WriteFloat64(z.Y2)
	if err != nil {
		return
	}
	return
}

// MarshalMsg implements msgp.Marshaler
func (z *Rect) MarshalMsg(b []byte) (o []byte, err error) {
	o = msgp.Require(b, z.Msgsize())
	// array header, size 4
	o = append(o, 0x94)
	o = msgp.AppendFloat64(o, z.X1)
	o = msgp.AppendFloat64(o, z.Y1)
	o = msgp.AppendFloat64(o, z.X2)
	o = msgp.AppendFloat64(o, z.Y2)
	return
}

// UnmarshalMsg implements msgp.Unmarshaler
func (z *Rect) UnmarshalMsg(bts []byte) (o []byte, err error) {
	var zmfd uint32
	zmfd, bts, err = msgp.ReadArrayHeaderBytes(bts)
	if err != nil {
		return
	}
	if zmfd != 4 {
		err = msgp.ArrayError{Wanted: 4, Got: zmfd}
		return
	}
	z.X1, bts, err = msgp.ReadFloat64Bytes(bts)
	if err != nil {
		return
	}
	z.Y1, bts, err = msgp.ReadFloat64Bytes(bts)
	if err != nil {
		return
	}
	z.X2, bts, err = msgp.ReadFloat64Bytes(bts)
	if err != nil {
		return
	}
	z.Y2, bts, err = msgp.ReadFloat64Bytes(bts)
	if err != nil {
		return
	}
	o = bts
	return
}

// Msgsize returns the number of bytes occupied by the serialized message
func (z *Rect) Msgsize() (s int) {
	s = 1 + msgp.Float64Size + msgp.Float64Size + msgp.Float64Size + msgp.Float64Size
	return
}

// DecodeMsg implements msgp.Decodable
func (z *Size) DecodeMsg(dc *msgp.Reader) (err error) {
	var zzdc uint32
	zzdc, err = dc.ReadArrayHeader()
	if err != nil {
		return
	}
	if zzdc != 2 {
		err = msgp.ArrayError{Wanted: 2, Got: zzdc}
		return
	}
	z.W, err = dc.ReadFloat64()
	if err != nil {
		return
	}
	z.H, err = dc.ReadFloat64()
	if err != nil {
		return
	}
	return
}

// EncodeMsg implements msgp.Encodable
func (z Size) EncodeMsg(en *msgp.Writer) (err error) {
	// array header, size 2
	err = en.Append(0x92)
	if err != nil {
		return err
	}
	err = en.WriteFloat64(z.W)
	if err != nil {
		return
	}
	err = en.WriteFloat64(z.H)
	if err != nil {
		return
	}
	return
}

// MarshalMsg implements msgp.Marshaler
func (z Size) MarshalMsg(b []byte) (o []byte, err error) {
	o = msgp.Require(b, z.Msgsize())
	// array header, size 2
	o = append(o, 0x92)
	o = msgp.AppendFloat64(o, z.W)
	o = msgp.AppendFloat64(o, z.H)
	return
}

// UnmarshalMsg implements msgp.Unmarshaler
func (z *Size) UnmarshalMsg(bts []byte) (o []byte, err error) {
	var zelx uint32
	zelx, bts, err = msgp.ReadArrayHeaderBytes(bts)
	if err != nil {
		return
	}
	if zelx != 2 {
		err = msgp.ArrayError{Wanted: 2, Got: zelx}
		return
	}
	z.W, bts, err = msgp.ReadFloat64Bytes(bts)
	if err != nil {
		return
	}
	z.H, bts, err = msgp.ReadFloat64Bytes(bts)
	if err != nil {
		return
	}
	o = bts
	return
}

// Msgsize returns the number of bytes occupied by the serialized message
func (z Size) Msgsize() (s int) {
	s = 1 + msgp.Float64Size + msgp.Float64Size
	return
}
