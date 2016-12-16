// -*- mode: csharp; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
//
// Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.
//

namespace Dogen.TestModels.CSharpModel
{
    /// <summary>
    /// Generates sequences of ComplexBuiltins.
    /// </summary>
	public static class ComplexBuiltinsDumper
    {
		static void Dump(DumpHelper helper, ComplexBuiltins value)
		{
			helper.IncrementDepth();
			if (helper.MaximumDepthExceeded())
				return;

			helper.AddStartObject();
			helper.AddType("Dogen.TestModels.CSharpModel.ComplexBuiltins", true/*withSeparator*/);
			helper.Add("ObjectProperty", value.ObjectProperty, true/*withSeparator*/);
			helper.Add("StringProperty", value.StringProperty);
			helper.AddEndObject();

			helper.DecrementDepth();
		}

		public static string Dump(ComplexBuiltins value)
        {
			var helper = new DumpHelper();
			Dump(helper, value);
			return helper.Dump();
        }
    }
}