package p2m

import "github.com/tinylib/msgp/msgp"

func (p *Path) decodeStrokeWidth(dc *msgp.Reader) (err error) {
	p.StrokeWidth, err = dc.ReadFloat64()
	return err
}

func (p *Path) decodePath(dc *msgp.Reader) (err error) {
	var zrjx uint32
	zrjx, err = dc.ReadArrayHeader()
	if err != nil {
		return
	}
	if cap(p.Data) >= int(zrjx) {
		p.Data = p.Data[:zrjx]
	} else {
		p.Data = make([][]float64, zrjx)
	}
	for zgmo := range p.Data {
		var zawn uint32
		zawn, err = dc.ReadArrayHeader()
		if err != nil {
			return
		}
		if cap(p.Data[zgmo]) >= int(zawn) {
			p.Data[zgmo] = p.Data[zgmo][:zawn]
		} else {
			p.Data[zgmo] = make([]float64, zawn)
		}
		for ztaf := range p.Data[zgmo] {
			p.Data[zgmo][ztaf], err = dc.ReadFloat64()
			if err != nil {
				return
			}
		}
	}
	return nil
}

func (p *Path) decodeColor(dc *msgp.Reader) (err error) {
	var sz uint32
	sz, err = dc.ReadArrayHeader()
	if err != nil {
		return
	}
	if sz != 3 {
		err = msgp.ArrayError{Wanted: 3, Got: sz}
		return
	}
	p.Color.R, err = dc.ReadUint8()
	if err != nil {
		return
	}
	p.Color.G, err = dc.ReadUint8()
	if err != nil {
		return
	}
	p.Color.B, err = dc.ReadUint8()
	if err != nil {
		return
	}
	return nil
}

// DecodeMsg implements msgp.Decodable
func (p *Path) DecodeMsg(dc *msgp.Reader) (err error) {
	var sz uint32
	sz, err = dc.ReadArrayHeader()
	if err != nil {
		return
	}
	if sz != 2 {
		err = msgp.ArrayError{Wanted: 2, Got: sz}
		return
	}

	err = p.Type.DecodeMsg(dc)
	if err != nil {
		return
	}

	switch p.Type {
	case PathTypeSetStrokeWidth:
		return p.decodeStrokeWidth(dc)
	case PathTypeEoFill, PathTypeStroke, PathTypeFill:
		return p.decodePath(dc)
	case PathTypeSetStrokeColor, PathTypeSetFillColor:
		return p.decodeColor(dc)

	default:
	}
	// Unimplemented
	return dc.Skip()
}
